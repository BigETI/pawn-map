#include <a_samp>
#include <map>

// Required by assert() and assertf()
#pragma tabsize 0

#define assert%2(%0,%1)%3; \
if (!(%0)) \
{ \
    print(%1); \
    return -1; \
}

#define assertf%3(%0,%1,%2)%4; \
if (!(%0)) \
{ \
    printf(%1,%2); \
    return -1; \
}

// Print map
PrintMap(Map:map)
{
    new key[128], value[128], key_size, value_size;
    printf("Map 0x%x:", _:map);
    MAP_foreach(k => v : map)
    {
        key_size = MEM_get_size(k);
        value_size = MEM_get_size(v);
        MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(key[0]), sizeof key);
        MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(value[0]), sizeof value);
        MEM_get_arr(k, _, key, (key_size < sizeof key) ? key_size : sizeof key);
        MEM_get_arr(v, _, value, (value_size < sizeof value) ? value_size : sizeof value);
        printf("0x%x => 0x%x, %d => %d, \"%s\" => \"%s\"", _:k, _:v, key_size, value_size, key, value);
    }
}

// On filter script init
public OnFilterScriptInit()
{
    new Map:test_map = MAP_NULL, c, buf[128];
    print("\r\n[MAPTEST] Test 1");
    PrintMap(test_map);
    c = MAP_count(test_map);
    assertf(c == 0, "Invalid count (%d, expected 0) : Test #1", c);
    print("\r\n[MAPTEST] Test 2");
    MAP_insert_str_str(test_map, "a", "b");
    MAP_insert_str_str(test_map, "cd", "ef");
    MAP_insert_str_str(test_map, "ghi", "jkl");
    MAP_insert_str_str(test_map, "m", "n");
    MAP_insert_str_str(test_map, "op", "qs");
    MAP_insert_str_str(test_map, "tuv", "wxy");
    PrintMap(test_map);
    c = MAP_count(test_map);
    assertf(c == 6, "Invalid count (%d, expected 6) : Test #2", c);
    print("\r\n[MAPTEST] Test 3");
    MAP_insert_str_str(test_map, "a", "xy");
    MAP_insert_str_str(test_map, "op", "z");
    PrintMap(test_map);
    c = MAP_count(test_map);
    assertf(c == 6, "Invalid count (%d, expected 6) : Test #3", c);
    print("\r\n[MAPTEST] Test 4");
    MAP_remove_str(test_map, "tuv");
    MAP_remove_str(test_map, "aaa");
    PrintMap(test_map);
    c = MAP_count(test_map);
    assertf(c == 5, "Invalid count (%d, expected 5) : Test #4", c);
    print("\r\n[MAPTEST] Test 5");
    MAP_get_str_arr(test_map, "ghi", buf);
    assertf(strcmp(buf, "jkl", false, 3) == 0, "Invalid value for \"ghi\" (\"%s\", expected \"jkl\") : Test #5", buf);
    print("\r\n[MAPTEST] Test 6");
    MAP_clear(test_map);
    PrintMap(test_map);
    c = MAP_count(test_map);
    assertf(c == 0, "Invalid count (%d, expected 0) : Test #6", c);
    print("[MAPTEST] Test completed.");
    print("\r\n==============================");
    print("= Map unit test filterscript =");
    print("=             Made by BigETI =");
    print("= Loaded!                    =");
    print("==============================\r\n");
    return 1;
}

// On filter script exit
public OnFilterScriptExit()
{
    print("\r\n==============================");
    print("= Map unit test filterscript =");
    print("=             Made by BigETI =");
    print("= Unloaded!                  =");
    print("==============================\r\n");
}