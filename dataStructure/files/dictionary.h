//
//  dictionary.h
//  dataStructure
//
//  Created by Jiabao Li on 2022/3/25.
//

#ifndef dictionary_h
#define dictionary_h

#include "ds_globalVars.h"
#include "uthash.h"


typedef struct {
    UT_hash_handle hh;
    char* key;
    void* ele_addr;
}HashNode;


typedef struct dictionary {
    void* (*ADD_EDIT_dict)(struct dictionary*, char*, void*);
    void* (*GET_dict)(struct dictionary*, char*);
    void* (*DEL_dict)(struct dictionary*, char*);
    HashNode* head;
    char* name;
    c8 ifinitial;
}Dictionary;


c8 InitDictionary(Dictionary *dict);
c8 CreateDictionary(Dictionary **dict);
void* add_edit_dict(Dictionary *dict, char* key, void* value);
void* get_dict(Dictionary* dict, char* key);
void* del_dict(Dictionary* dict, char* key);






#endif /* dictionary_h */
