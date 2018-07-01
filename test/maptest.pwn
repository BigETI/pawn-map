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
        printf("\t0x%x => 0x%x, %d => %d, \"%s\" => \"%s\"", _:k, _:v, key_size, value_size, key, value);
    }
}

// Print maps in map
PrintMapsInMap(Map:map)
{
    new key[128], value[128], key_size, value_size, Map:m;
    printf("Map 0x%x:", _:map);
    MAP_foreach(kx => vx : map)
    {
        key_size = MEM_get_size(kx);
        value_size = MEM_get_size(vx);
        if (value_size == 1)
        {
            m = Map:MEM_get_val(vx, 0);
            if (m != MAP_NULL)
            {
                if (MEM_get_size(Pointer:m) == MAP_struct)
                {
                    printf("\tMap 0x%x:", _:m);
                    MAP_foreach(ky => vy : m)
                    {
                        key_size = MEM_get_size(ky);
                        value_size = MEM_get_size(vy);
                        MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(key[0]), sizeof key);
                        MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(value[0]), sizeof value);
                        MEM_get_arr(ky, _, key, (key_size < sizeof key) ? key_size : sizeof key);
                        MEM_get_arr(vy, _, value, (value_size < sizeof value) ? value_size : sizeof value);
                        printf("\t\t0x%x => 0x%x, %d => %d, \"%s\" => \"%s\"", _:ky, _:vy, key_size, value_size, key, value);
                    }
                }
                else
                {
                    MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(key[0]), sizeof key);
                    MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(value[0]), sizeof value);
                    MEM_get_arr(kx, _, key, (key_size < sizeof key) ? key_size : sizeof key);
                    MEM_get_arr(vx, _, value, (value_size < sizeof value) ? value_size : sizeof value);
                    printf("\t0x%x => 0x%x, %d => %d, \"%s\" => \"%s\"", _:kx, _:vx, key_size, value_size, key, value);
                }
            }
            else
            {
                MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(key[0]), sizeof key);
                MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(value[0]), sizeof value);
                MEM_get_arr(kx, _, key, (key_size < sizeof key) ? key_size : sizeof key);
                MEM_get_arr(vx, _, value, (value_size < sizeof value) ? value_size : sizeof value);
                printf("\t0x%x => 0x%x, %d => %d, \"%s\" => \"%s\"", _:kx, _:vx, key_size, value_size, key, value);
            }
        }
        else
        {
            MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(key[0]), sizeof key);
            MEM_UM_zero(UnmanagedPointer:MEM_UM_get_addr(value[0]), sizeof value);
            MEM_get_arr(kx, _, key, (key_size < sizeof key) ? key_size : sizeof key);
            MEM_get_arr(vx, _, value, (value_size < sizeof value) ? value_size : sizeof value);
            printf("\t0x%x => 0x%x, %d => %d, \"%s\" => \"%s\"", _:kx, _:vx, key_size, value_size, key, value);
        }
    }
}

// Entry point
main()
{
    new Map:test_map = MAP_NULL, Map:test_map_a = MAP_NULL, Map:test_map_b = MAP_NULL, c, buf[128];
    print("\r\n==================");
    print("= Map unit test  =");
    print("= Made by BigETI =");
    print("= Loaded!        =");
    print("==================\r\n");
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
    print("\r\n[MAPTEST] Test 7");
    MAP_insert_str_str(test_map_a, "a", "b");
    MAP_insert_str_str(test_map_a, "cd", "ef");
    MAP_insert_str_str(test_map_a, "ghi", "jkl");
    MAP_insert_str_str(test_map_b, "m", "n");
    MAP_insert_str_str(test_map_b, "op", "qs");
    MAP_insert_str_str(test_map_b, "tuv", "wxy");
    MAP_insert_str_val(test_map, "map a", _:test_map_a);
    MAP_insert_str_val(test_map, "map b", _:test_map_b);
    PrintMapsInMap(test_map);
    c = MAP_count(test_map);
    assertf(c == 2, "Invalid count (%d, expected 2) : Test #7", c);
    c = MAP_count(test_map_a);
    assertf(c == 3, "Invalid count (%d, expected 3) : Test #7", c);
    c = MAP_count(test_map_b);
    assertf(c == 3, "Invalid count (%d, expected 3) : Test #7", c);
    print("\r\n[MAPTEST] Test 8");
    MAP_clear(test_map);
    MAP_clear(test_map_a);
    MAP_clear(test_map_b);
    c = MAP_count(test_map);
    assertf(c == 0, "Invalid count (%d, expected 0) : Test #8", c);
    c = MAP_count(test_map_a);
    assertf(c == 0, "Invalid count (%d, expected 0) : Test #8", c);
    c = MAP_count(test_map_b);
    assertf(c == 0, "Invalid count (%d, expected 0) : Test #8", c);
    print("[MAPTEST] Test completed.");
    return 1;
}
