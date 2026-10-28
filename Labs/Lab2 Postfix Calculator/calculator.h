#include "in2post.h"
#include "postfix_cal.h"
#include "string2vec.h"

int cal(string expression){
    vector<string> in_str_vec = string2vec(expression);
    vector<string> post_str_vec = in2post(in_str_vec);
    int result = postfix_cal(post_str_vec);
    return result;
}