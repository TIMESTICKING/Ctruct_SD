<h3 align="center">Dictionary</h3>

---

<p align="left">Dictionary is based on a hash algorithm "<a href="https://troydhanson.github.io/uthash/">uthash</a>".</p>

It contains two properties. The first one is maintained by the program, you should only care about the others.
```clike
    HashNode* head;
    char* name;
```

# create or initialize
```clike
    Dictionary mydict;
    InitDictionary(&mydict);
    mydict.name = "dict1";//rename it

    // or

    Dictionary* mydict;
    InitDictionary(&mydict);
    mydict->name = "dict1";//rename it
```

# functions

#### void* ADD_EDIT_dict(struct dictionary*, char* key, void* value)

Add or edit the `value` corresponding to the `key`. Like
```clike
    mydict.ADD_EDIT_dict(&mydict,"number",INT_new(3)); //keys and values
    mydict.ADD_EDIT_dict(&mydict,"string","hello my baby~");
```

Success if it returns `ARR_OK` or any other address `x`. `x` represents the address of the old element you replaced, in case if you need to **free the memory** of it.

#### void* GET_dict(struct dictionary*, char* key)

Get the pointer of the value by the key you provide. Like
```clike
int* res;
res = (int*)mydict.GET_dict(&mydict, "number");
SD_PRINT("res is: %d", *res);
```
or
```clike
void* res3 = mydict.GET_dict(&mydict, "string");
if (res3)
    SD_PRINT("res is: %s", (char*)res3);
```

Success if it returns an address `x`.

No such a key if it returns `ARR_FALSE`.

#### void* DEL_dict(struct dictionary*, char* key)

Delete a key-value pair from the dictionary.

It is okay if the key doesn't exist, it'll return `ARR_OK`

If the key exists, return the address in case if you need to free the memory of it. 

