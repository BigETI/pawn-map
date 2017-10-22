# Map implementation in PAWN

## Notes
Using `Map::` is equivalent to using `MAP_`, for example:
```C
MAP::insert_val_val(map, 1, 2);
// Is equivalent to
MAP_insert_val_val(map, 1, 2);
```

## Important
Use `MAP_clear` if you don't need your map anymore, to prevent memory leaks!

## Documentation (Functions)

### MAP_insert_val_val
#### Description
Map insert (key, value)
#### Syntax
```C
MAP_insert_val_val(&Map:map, key, value)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 0);
```

### MAP_insert_val_arr
#### Description
Map insert (key, value[])
####Syntax
```C
MAP_insert_val_arr(&Map:map, key, const value[], value_size = sizeof value)
```
#### Example
```C
new Map:map, arr[10] = {100, ...};
MAP_insert_val_arr(map, 1, arr);
```

### MAP_insert_arr_val
####Description
Map insert (key[], value)
####Syntax
```C
MAP_insert_arr_val(&Map:map, const key[], key_size = sizeof key, value)
```
#### Example
```C
new Map:map, arr[10] = {100, ...};
MAP_insert_arr_val(map, arr, 1);
```

### MAP_insert_arr_arr
#### Description
Map insert (key[], value[])
#### Syntax
```C
MAP_insert_arr_arr(&Map:map, const key[], key_size = sizeof key, const value[], value_size = sizeof value)
```
#### Example
```C
new Map:map, arr1[10] = {100, ...}, arr2[20] = {200, ...};
MAP_insert_arr_arr(map, arr1, _, arr2);
```

### MAP_insert_val_str
#### Description
Map insert (key, value[] as string)
#### Syntax
```C
MAP_insert_val_str(&Map:map, key, const value[])
```
#### Example
```C
new Map:map;
MAP_insert_val_str(map, 1, "This is a test.");
```

### MAP_insert_arr_str
#### Description
Map insert (key[], value[] as string)
#### Syntax
```C
MAP_insert_arr_str(&Map:map, const key[], key_size = sizeof key, const value[])
```
#### Example
```C
new Map:map, arr[10] = {100, ...};
MAP_insert_arr_str(map, arr, _, "This is a test.");
```

### MAP_insert_str_str
#### Description
Map insert (key[] as string, value[] as string)
#### Syntax
```C
MAP_insert_str_str(&Map:map, const key[], const value[])
```
#### Example
```C
new Map:map;
MAP_insert_str_str(map, "This is a test.", "foo");
```

### MAP_insert_str_val
#### Description
Map insert (key[] as string, value)
#### Syntax
```C
MAP_insert_str_val(&Map:map, const key[], value)
```
#### Example
```C
new Map:map;
MAP_insert_str_val(map, "This is a test", 1);
```

### MAP_insert_str_arr
#### Description
Map insert (key[] as string, value)
#### Syntax
```C
MAP_insert_str_arr(&Map:map, const key[], const value[], value_size = sizeof value)
```
#### Example
```C
new Map:map, arr[10] = {100, ...};
MAP_insert_str_arr(map, "This is a test.", arr);
```

### MAP_get_ptr_size_val
#### Description
Map get pointer and size (key)
#### Returns
Pointer of the value, otherwise `MAP_MEM_NULL`
#### Syntax
```C
Pointer:MAP_get_ptr_size_val(Map:map, key, &value_size)
```
#### Example
```C
new Map:map, Pointer:ptr, value_size;
MAP_insert_val_str(map, 1, "This is a test.");
ptr = MAP_get_ptr_size_val(map, 1, value_size);
if (ptr == MAP_MEM_NULL)
{
	print("Value not found.");
}
else
{
	printf("Value pointer: 0x%x", _:ptr);
	printf("Value size: %d", value_size);
}
```

### MAP_get_ptr_size_arr
#### Description
Map get pointer and size (key[])
#### Returns
Pointer of the value, otherwise `MAP_MEM_NULL`
#### Syntax
```C
Pointer:MAP_get_ptr_size_arr(Map:map, const key[], key_size, &value_size)
```
#### Example
```C
new Map:map, arr[10] = {100, ...}, Pointer:ptr, value_size;
MAP_insert_arr_str(map, arr, _, "This is a test.");
ptr = MAP_get_ptr_size_arr(map, arr, value_size);
if (ptr == MAP_MEM_NULL)
{
	print("Value not found.");
}
else
{
	printf("Value pointer: 0x%x", _:ptr);
	printf("Value size: %d", value_size);
}
```

### MAP_get_ptr_size_str
#### Description
Map get pointer and size (key[] as string)
#### Returns
Pointer of the value, otherwise `MAP_MEM_NULL`
#### Syntax
```C
Pointer:MAP_get_ptr_size_str(Map:map, const key[], &value_size)
```
#### Example
```C
new Map:map, Pointer:ptr, value_size;
MAP_insert_str_str(map, "This is a test.", "foo");
ptr = MAP_get_ptr_size_str(map, "This is a test.", value_size);
if (ptr == MAP_MEM_NULL)
{
	print("Value not found.");
}
else
{
	printf("Value pointer: 0x%x", _:ptr);
	printf("Value size: %d", value_size);
}
```

### MAP_contains_val
#### Description
Map contains (key)
#### Returns
`true` if successful, otherwise `false`
#### Syntax
```C
bool:MAP_contains_val(Map:map, key)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
printf("Value%s found", (MAP_contains_val(map, 1) ? ("") : (" not")));
```

### MAP_contains_arr
#### Description
Map contains (key[])
#### Returns
`true` if successful, otherwise `false`
#### Syntax
```C
bool:MAP_contains_arr(Map:map, const key[], key_size = sizeof key)
```
#### Example
```C
new Map:map, arr[10] = {100, ...};
MAP_insert_arr_val(map, arr, _, 1);
printf("Value%s found", (MAP_contains_arr(map, arr) ? ("") : (" not")));
```

### MAP_contains_str
#### Description
Map contains (key[] as string)
#### Returns
`true` if successful, otherwise `false`
#### Syntax
```C
bool:MAP_contains_str(Map:map, const key[])
```
Example
```C
new Map:map;
MAP_insert_str_val(map, "This is a test.", 1);
printf("Value%s found", (MAP_contains_str(map, "This is a test.") ? ("") : (" not")));
```

### MAP_get_val_val
#### Description
Map get value (key)
#### Returns
The value if successful, otherwise `0`
#### Syntax
```C
MAP_get_val_val(Map:map, key)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
printf("The value for 1 is %d", MAP_get_val_val(map, 1));
```

### MAP_get_val_arr
#### Description
Map get array (key)
#### Syntax
```C
MAP_get_val_arr(Map:map, key, value[], value_size = sizeof value)
```
#### Example
```C
new Map:map, arr1[10] = {100, ...}, arr2[sizeof arr1];
MAP_insert(map, 1, arr1);
MAP_get_val_arr(map, 1, arr2);
for (new i; i < sizeof arr2; i++)
{
	printf("arr2[%d] = %d", i, arr2[i]);
}
```

### MAP_get_arr_val
#### Description
Map get value (key[])
#### Returns
The value if successful, otherwise `0`
#### Syntax
```C
MAP_get_arr_val(Map:map, const key[], key_size = sizeof key)
```
#### Example
```C
new Map:map, arr[10] = {100, ...};
MAP_insert_arr_val(map, arr, _, 1);
printf("The value for arr is %d", MAP_get_arr_val(map, arr));
```

### MAP_get_arr_arr
#### Description
Map get array (key[])
#### Syntax
```C
MAP_get_arr_arr(Map:map, const key[], key_size = sizeof key, value[], value_size = sizeof value)
```
#### Example
```C
new Map:map, arr1[10] = {100, ...}, arr2[20] = {200, ...}, arr3[sizeof arr3];
MAP_insert_arr_arr(map, arr1, _, arr2);
MAP_get_arr_arr(map, arr1, _, arr3);
for (new i; i < sizeof arr3; i++)
{
	printf("arr3[%d] = %d", i, arr3[i]);
}
```

### MAP_get_str_val
#### Description
Map get value (key[] as string)
#### Returns
The value if successful, otherwise `0`
#### Syntax
```C
MAP_get_str_val(Map:map, const key[])
```
#### Example
```C
new Map:map;
MAP_insert_str_val(map, "This is a test.", 1);
printf("The value for \"This is a test.\" is %d", MAP_get_str_val(map, "This is a test."));
```

### MAP_get_str_arr
#### Description
Map get array (key[] as string)
#### Syntax
```C
MAP_get_str_arr(Map:map, const key[], value[], value_size = sizeof value)
```
#### Example
```C
new Map:map, arr[10] = {100, ...}, arr2[sizeof arr1];
MAP_insert_str_arr(map, "This is a test.", arr1);
MAP_get_str_arr(map, "This is a test.", arr2);
for (new i; i < sizeof arr2; i++)
{
	printf("arr2[%d] = %d", i, arr2[i]);
}
```
or
```C
new Map:map, str[4];
MAP_insert_str_arr(map, "This is a test.", "foo");
MAP_get_str_arr(map, "This is a test.", str);
printf("The value for \"This is a test.\" is \"%s\"", str);
```

### MAP_count
#### Description
Count the nodes in `map`
#### Returns
Number of nodes in `map`
#### Syntax
```C
MAP_count(Map:map)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
MAP_insert_val_val(map, 3, 4);
MAP_insert_val_val(map, 5, 6);
printf("Number of nodes in map: %d", MAP_count(map));
```

### MAP_remove_val
#### Description
Map remove (key)
#### Syntax
```C
MAP_remove_val(&Map:map, key)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
MAP_insert_val_val(map, 3, 4);
MAP_insert_val_val(map, 5, 6);
MAP_remove_val(map, 3);
```

### MAP_remove_arr
#### Description
Map remove (key[])
#### Syntax
```C
MAP_remove_arr(&Map:map, const key[], key_size = sizeof key)
```
#### Example
```C
new Map:map, arr1[10] = {100, ...}, arr2[20] = {200, ...}, arr3[30] = {300, ...};
MAP_insert_arr_val(map, arr1, _, 1);
MAP_insert_arr_val(map, arr2, _, 2);
MAP_insert_arr_val(map, arr3, _, 3);
MAP_remove_arr(map, arr2);
```

### MAP_remove_str
#### Description
Map remove (key[] as string)
#### Syntax
```C
MAP_remove_str(&Map:map, const key[])
```
#### Example
```C
MAP_insert_str_val(map, "This is a test.", 1);
MAP_insert_str_val(map, "foo", 2);
MAP_insert_str_val(map, "bar", 3);
MAP_remove_str(map, "foo");
```

### MAP_clear
#### Description
Clear map
#### Syntax
```C
MAP_clear(&Map:map)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
MAP_insert_val_val(map, 3, 4);
MAP_insert_val_val(map, 5, 6);
MAP_clear(map);
```

### MAP_iter_get
#### Description
Map iterator get
#### Returns
The value specified in `map`
#### Syntax
```C
Map:MAP_iter_get(Map:map, &Pointer:key_ptr, &Pointer:value_ptr, &key_size, &value_size)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
MAP_insert_val_val(map, 3, 4);
MAP_insert_val_val(map, 5, 6);
for (new Pointer:key_ptr, Pointer:value_ptr, key_size, value_size, Map:temp_map = MAP_iter_get(map, key_ptr, value_ptr, key_size, value_size); temp_map != MAP_NULL; temp_map = MAP_iter_next(temp_map, MAP_NULL, key_ptr, value_ptr, key_size, key_value))
{
	//
}
```

### MAP_iter_next
#### Description
Map iterator next
#### Returns
Next map iterator from map iterator
#### Syntax
```C
Map:MAP_iter_get(Map:map, &Pointer:key_ptr, &Pointer:value_ptr, &key_size, &value_size)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
MAP_insert_val_val(map, 3, 4);
MAP_insert_val_val(map, 5, 6);
for (new Pointer:key_ptr, Pointer:value_ptr, key_size, value_size, Map:temp_map = MAP_iter_get(map, key_ptr, value_ptr, key_size, value_size); temp_map != MAP_NULL; temp_map = MAP_iter_next(temp_map, MAP_NULL, key_ptr, value_ptr, key_size, key_value))
{
	//
}
```

## Documentation (Definitions)

### MAP_MEM_NULL
#### Description
A null pointer

### MAP_NULL
#### Description
Empty map (null pointer)

### MAP_foreach
#### Description
Method to traverse through a map
#### Syntax
```C
MAP_foreach(Map:map : Pointer:key => Pointer:value, key_size => value_size)
```
#### Example
```C
new Map:map;
MAP_insert_val_val(map, 1, 2);
MAP_insert_val_val(map, 3, 4);
MAP_insert_val_val(map, 5, 6);
MAP::foreach(map : k => v, k_sz => v_sz)
{
	printf("0x%x => 0x%x, %d => %d, \"%d\" => \"%d\"", _:k, _:v, k_sz, v_sz, MEM::get_val(k, _), MEM::get_val(v, _));
}
```
or
```C
new Map:map, arr1[10] = {100, ...}, arr2[20] = {200, ...}, arr3[30] = {300, ...}, arr4[40] = {400, ...}, arr5[50] = {500, ...}, arr6[60] = {600, ...}, key[60], value[60], m_k_sz, m_v_sz;
MAP_insert_arr_arr(map, arr1, _, arr2);
MAP_insert_arr_arr(map, arr3, _, arr4);
MAP_insert_arr_arr(map, arr5, _, arr6);
MAP::foreach(map : k => v, k_sz => v_sz)
{
	m_k_sz = ((k_sz < sizeof key) ? k_sz : sizeof key);
	m_v_sz = ((v_sz < sizeof value) ? v_sz : sizeof value);
	MEM::zero(MEM::get_addr(key[0]), sizeof key);
	MEM::zero(MEM::get_addr(value[0]), sizeof value);
	MEM::get_arr(k, _, key, m_k_sz);
	MEM::get_arr(v, _, value, m_v_sz);
	printf("0x%x => 0x%x, %d => %d", _:k, _:v, k_sz, v_sz);
	print("\tKey:");
	for (new i = 0; i < m_k_sz; i++)
	{
		printf("\t\t0x%x", key[i]);
	}
	print("\tValue:");
	for (new i = 0; i < m_v_sz; i++)
	{
		printf("\t\t0x%x", value[i]);
	}
}
```
or
```C
new Map:map, key[16], value[6], m_k_sz, m_v_sz;
MAP_insert_str_str(map, "This is a test.", "foo");
MAP_insert_str_str(map, "bar", "lorem");
MAP_insert_str_str(map, "ipsum", "dolor");
MAP::foreach(map : k => v, k_sz => v_sz)
{
	m_k_sz = ((k_sz < sizeof key) ? k_sz : sizeof key);
	m_v_sz = ((v_sz < sizeof value) ? v_sz : sizeof value);
	MEM::zero(MEM::get_addr(key[0]), sizeof key);
	MEM::zero(MEM::get_addr(value[0]), sizeof value);
	MEM::get_arr(k, _, key, m_k_sz);
	MEM::get_arr(v, _, value, m_v_sz);
	printf("0x%x => 0x%x, %d => %d, \"%s\" => \"%s\"", _:k, _:v, k_sz, v_sz, key, value);
}
```
