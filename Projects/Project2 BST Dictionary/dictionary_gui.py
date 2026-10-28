import tkinter as tk
from tkinter import messagebox, scrolledtext
import ctypes
import os
import platform

# --- C++ Library Loading and Function Prototyping ---

# Determine the library file name based on the OS
lib_name = 'dictionary_lib.dll' if platform.system() == "Windows" else "dictionary_lib.so"
lib_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), lib_name)

if not os.path.exists(lib_path):
    messagebox.showerror("Error", f"Library not found: {lib_path}\nPlease compile the C++ code first by running 'make' in the terminal.")
    exit()

# Load the shared library
lib = ctypes.CDLL(lib_path)

# --- Prototype C++ functions ---

# create_dictionary() -> void*
lib.create_dictionary.restype = ctypes.c_void_p

# destroy_dictionary(void*)
lib.destroy_dictionary.argtypes = [ctypes.c_void_p]

# search_word(void*, char*) -> char*
lib.search_word.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
lib.search_word.restype = ctypes.c_void_p  # 改为 c_void_p 避免自动释放

# add_word(void*, char*, char*) -> int
lib.add_word.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
lib.add_word.restype = ctypes.c_int

# delete_word(void*, char*) -> int
lib.delete_word.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
lib.delete_word.restype = ctypes.c_int

# free_string(char*)
lib.free_string.argtypes = [ctypes.c_char_p]

# --- Main Application Class ---

class DictionaryApp:
    def __init__(self, root):
        self.root = root
        self.root.title("BST Dictionary")
        self.root.geometry("500x450")

        # Initialize the C++ dictionary
        self.dict_ptr = lib.create_dictionary()

        # --- GUI Widgets ---
        
        # Frame for inputs
        input_frame = tk.Frame(root, padx=10, pady=10)
        input_frame.pack(fill=tk.X)

        # Search/Delete Entry
        tk.Label(input_frame, text="Word:").grid(row=0, column=0, sticky="w")
        self.word_entry = tk.Entry(input_frame, width=30)
        self.word_entry.grid(row=0, column=1, padx=5)

        # Meaning Entry (for adding)
        tk.Label(input_frame, text="Meaning:").grid(row=1, column=0, sticky="w", pady=5)
        self.meaning_entry = tk.Entry(input_frame, width=30)
        self.meaning_entry.grid(row=1, column=1, padx=5, pady=5)

        # Frame for buttons
        button_frame = tk.Frame(root, pady=5)
        button_frame.pack()

        self.search_button = tk.Button(button_frame, text="Search", command=self.search_word)
        self.search_button.pack(side=tk.LEFT, padx=5)

        self.add_button = tk.Button(button_frame, text="Add/Update", command=self.add_word)
        self.add_button.pack(side=tk.LEFT, padx=5)

        self.delete_button = tk.Button(button_frame, text="Delete", command=self.delete_word)
        self.delete_button.pack(side=tk.LEFT, padx=5)

        # Frame for results
        results_frame = tk.Frame(root, padx=10, pady=5)
        results_frame.pack(fill=tk.BOTH, expand=True)

        tk.Label(results_frame, text="Results:").pack(anchor="w")
        self.results_text = scrolledtext.ScrolledText(results_frame, wrap=tk.WORD, height=15)
        self.results_text.pack(fill=tk.BOTH, expand=True)
        self.results_text.config(state=tk.DISABLED) # Make it read-only

        # Bind the closing of the window to a cleanup function
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)

    def search_word(self):
        word = self.word_entry.get()
        if not word:
            messagebox.showwarning("Input Error", "Please enter a word to search.")
            return

        try:
            # Call C++ function
            result_ptr = lib.search_word(self.dict_ptr, word.encode('utf-8'))
        except Exception as e:
            messagebox.showerror("C++ Error", f"Search failed: {e}")
            return

        self.results_text.config(state=tk.NORMAL)
        self.results_text.delete('1.0', tk.END)

        if result_ptr:
            try:
                # 手动从 void* 指针读取字符串
                result_str = ctypes.string_at(result_ptr).decode('utf-8')
                self.results_text.insert(tk.END, result_str)
            except Exception as e:
                self.results_text.insert(tk.END, f"(Decode error: {e})")
            finally:
                # Free the memory allocated by C++
                lib.free_string(ctypes.c_char_p(result_ptr))
        else:
            self.results_text.insert(tk.END, "No words found.")

        self.results_text.config(state=tk.DISABLED)

    def add_word(self):
        word = self.word_entry.get()
        meaning = self.meaning_entry.get()

        if not word or not meaning:
            messagebox.showwarning("Input Error", "Please provide both a word and its meaning.")
            return

        # Call C++ function
        result = lib.add_word(self.dict_ptr, word.encode('utf-8'), meaning.encode('utf-8'))

        if result == 1:
            messagebox.showinfo("Success", f"Successfully added '{word}'.")
        elif result == 0:
            messagebox.showinfo("Success", f"Successfully updated '{word}'.")
        else:
            messagebox.showerror("Error", "Failed to add or update the word.")
        
        # Clear entries after adding
        self.word_entry.delete(0, tk.END)
        self.meaning_entry.delete(0, tk.END)

    def delete_word(self):
        word = self.word_entry.get()
        if not word:
            messagebox.showwarning("Input Error", "Please enter a word to delete.")
            return

        # Call C++ function
        result = lib.delete_word(self.dict_ptr, word.encode('utf-8'))

        if result == 1:
            messagebox.showinfo("Success", f"Successfully deleted '{word}'.")
        else:
            messagebox.showerror("Not Found", f"The word '{word}' was not found in the dictionary.")
        
        self.word_entry.delete(0, tk.END)

    def on_closing(self):
        # Clean up the C++ dictionary before closing the app
        if messagebox.askokcancel("Quit", "Do you want to quit?"):
            print("Cleaning up C++ resources...")
            lib.destroy_dictionary(self.dict_ptr)
            self.root.destroy()

if __name__ == "__main__":
    main_window = tk.Tk()
    app = DictionaryApp(main_window)
    main_window.mainloop()
