//
//  dictionary.c
//  dataStructure
//
//  Created by Jiabao Li on 2022/3/25.
//

#include <stdio.h>
#include "dictionary.h"


/// init Dictionary struct
/// @param dict : a Dictionary var address
/// @return 1:ARR_OK
c8 InitDictionary(Dictionary *dict){
    HashNode* head=NULL;
    dict->ifinitial = 1;
    dict->name = "dictionary_def";
    dict->head = head;
    
    dict->ADD_EDIT_dict = add_edit_dict;
    dict->DEL_dict = del_dict;
    dict->GET_dict = get_dict;
    
    return ARR_OK;
}


/// dynamicly create dict
/// @param dict addr of dict pointer
/// @return 1:ARR_OK    3:ARR_MALLOC_FAIL
c8 CreateDictionary(Dictionary **dict){
    *dict = (Dictionary*)SD_MALLOC(sizeof(Dictionary));
    if (*dict == (Dictionary*)0)
        return ARR_MALLOC_FAIL;
    
    return InitDictionary(*dict);
}



/// add or edit an element into dict
/// @param dict dict addr
/// @param keyv a char str
/// @param value ele addr
/// @return 1:ARR_OK    3:ARR_MALLOC_FAIL -5:un init    x: replaced ele addr
void* add_edit_dict(Dictionary *dict, char* keyv, void* value){
    CHECK_INIT(dict, void*);
    
    HashNode *node;
    node = (HashNode*)SD_MALLOC(sizeof(HashNode));
    if (node == (HashNode*)0)
        return (void*)ARR_MALLOC_FAIL;
    
    node->ele_addr = value;
    node->key = keyv;
    
//    check uniqueness
    HashNode *s;
    HASH_FIND_STR(dict->head, keyv, s);
    if (s == NULL) {
        HASH_ADD_STR(dict->head, key, node);
    }else{
        HASH_REPLACE_STR(dict->head, key, node, s);
        if (SD_DEBUG){
            SD_PRINT_HEAD("Dictionary", "multiple key! replaced");
            SD_PRINT("dict name: %s, key name: %s", dict->name, keyv);
            SD_PRINT_END;
        }
        // get ele addr from the hashnode
        void* ele;
        ele = s->ele_addr;
        SD_FREE(s);
        return ele;
    }
    
    return (void*)ARR_OK;
}



/// get ele addr from dict
/// @param dict dict addr
/// @param keyv key str
/// @return 0: no such ele    -5:un init    x: ele addr
void* get_dict(Dictionary* dict, char* keyv){
    CHECK_INIT(dict, void*);
    
    HashNode *res;
    HASH_FIND_STR(dict->head, keyv, res);
    if (res == NULL){
        return ARR_FALSE;
    }
    
    return res->ele_addr;
}



/// del an ele from dict
/// @param dict dict addr
/// @param keyv key str
/// @return -5: un init     1:ARR_OK    x: deleted ele addr
void* del_dict(Dictionary* dict, char* keyv){
    CHECK_INIT(dict, void*);
    
    HashNode *res;
    HASH_FIND_STR(dict->head, keyv, res);
    if (res != NULL){
        void* ele;
        HASH_DEL(dict->head, res);
        ele = res->ele_addr;
        SD_FREE(res);
        
        return ele;
    }
    
    return (void*)ARR_OK;
}



void delete_all_dict(Dictionary* dict) {
  HashNode *current_user, *tmp;

  HASH_ITER(hh, dict->head, current_user, tmp) {
    HASH_DEL(dict->head, current_user);  /* delete; users advances to next */
    free(current_user);             /* optional- if you want to free  */
      // havent done yet!!!!!!!!!!!!!!. free bridger
  }
}





