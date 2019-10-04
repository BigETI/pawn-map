#if defined __MAP_INCLUDED__
    #endinput
#endif
#define __MAP_INCLUDED__

#include <memory>
#include <string>
    
#define MAP_NULL                        Map:MEM_NULLPTR
#define MAP_foreach%3(%0=>%1:%2)        MAP_foreach_ex%3(%0=>%1,__map__%0:%2)
#define MAP_foreach_ex%4(%0=>%1,%2:%3)  for%4(new Pointer:%0, Pointer:%1, Map:%2 = MAP_iter_get(%3, %0, %1); %2 != MAP_NULL; %2 = MAP_iter_next(%2, MAP_NULL, %0, %1))
#define __map__%0\32;                   __map__

// Map structure
MEM_struct MAP_struct
{
    Map:MAP_struct_left,
    Map:MAP_struct_right,
    Map:MAP_struct_parent,
    MAP_struct_key_hash,
    Pointer:MAP_struct_key_ptr,
    Pointer:MAP_struct_value_ptr
}

// Map hash key
// From Java String hashCode(): s[0]*31^(n - 1) + s[1]*31^(n - 2) + ... + s[n - 1]
static stock MAP_hash_key(Pointer:key_ptr)
{
    new ret;
    for (new i, sz = MEM_get_size(key_ptr); i < sz; i++)
    {
        ret = (31 * ret) + MEM_get_val(key_ptr, i);
    }
    return ret;
}

// Map node compare
static stock MAP_node_compare(Map:map, key_hash, Pointer:key_ptr)
{
    new ret;
    if (map != MAP_NULL)
    {
        new m[MAP_struct], ok, nk;
        MEM_get_arr(Pointer:map, _, m);
        if (key_hash < m[MAP_struct_key_hash])
        {
            ret = -1;
        }
        else if (key_hash > m[MAP_struct_key_hash])
        {
            ret = 1;
        }
        else
        {
            new key_size = MEM_get_size(key_ptr), other_key_size = MEM_get_size(m[MAP_struct_key_ptr]);
            if (key_size < other_key_size)
            {
                ret = -1;
            }
            else if (key_size > other_key_size)
            {
                ret = 1;
            }
            else
            {
                for (new i = 0; i < key_size; i++)
                {
                    ok = MEM_get_val(m[MAP_struct_key_ptr], i);
                    nk = MEM_get_val(key_ptr, i);
                    if (nk < ok)
                    {
                        ret = -1;
                        break;
                    }
                    else if (nk > ok)
                    {
                        ret = 1;
                        break;
                    }
                }
            }
        }
    }
    return ret;
}

// Map insert
static stock MAP_insert(&Map:map, Pointer:key_ptr, Pointer:value_ptr)
{
    if (map == MAP_NULL)
    {
        new m[MAP_struct];
        m[MAP_struct_key_hash] = MAP_hash_key(key_ptr);
        m[MAP_struct_key_ptr] = MEM_clone(key_ptr);
        m[MAP_struct_value_ptr] = MEM_clone(value_ptr);
        map = Map:MEM_new_arr(m);
    }
    else
    {
        new Map:om = map, Map:nm, c, key_hash = MAP_hash_key(key_ptr);
        while (om != MAP_NULL)
        {
            c = MAP_node_compare(om, key_hash, key_ptr);
            if (c < 0)
            {
                nm = Map:MEM_get_val(Pointer:om, _:MAP_struct_left);
                if (nm == MAP_NULL)
                {
                    new m[MAP_struct];
                    m[MAP_struct_parent] = om;
                    m[MAP_struct_key_hash] = key_hash;
                    m[MAP_struct_key_ptr] = MEM_clone(key_ptr);
                    m[MAP_struct_value_ptr] = MEM_clone(value_ptr);
                    nm = Map:MEM_new_arr(m);
                    if (nm != MAP_NULL)
                    {
                        MEM_set_val(Pointer:om, _:MAP_struct_left, _:nm);
                    }
                    break;
                }
                else
                {
                    om = nm;
                }
            }
            else if (c > 0)
            {
                nm = Map:MEM_get_val(Pointer:om, _:MAP_struct_right);
                if (nm == MAP_NULL)
                {
                    new m[MAP_struct];
                    m[MAP_struct_parent] = om;
                    m[MAP_struct_key_hash] = key_hash;
                    m[MAP_struct_key_ptr] = MEM_clone(key_ptr);
                    m[MAP_struct_value_ptr] = MEM_clone(value_ptr);
                    nm = Map:MEM_new_arr(m);
                    if (nm != MAP_NULL)
                    {
                        MEM_set_val(Pointer:om, _:MAP_struct_right, _:nm);
                    }
                    break;
                }
                else
                {
                    om = nm;
                }
            }
            else
            {
                MEM_set_val(Pointer:om, _:MAP_struct_value_ptr, _:MEM_clone(value_ptr));
                break;
            }
        }
    }
}

// Map find
static stock Map:MAP_find(Map:map, Pointer:key_ptr)
{
    new Map:ret, Map:om = map, c, key_hash = MAP_hash_key(key_ptr);
    while (om != MAP_NULL)
    {
        c = MAP_node_compare(om, key_hash, key_ptr);
        if (c < 0)
        {
            om = Map:MEM_get_val(Pointer:om, _:MAP_struct_left);
        }
        else if (c > 0)
        {
            om = Map:MEM_get_val(Pointer:om, _:MAP_struct_right);
        }
        else
        {
            ret = om;
            break;
        }
    }
    return ret;
}

// Map get value pointer
static stock Pointer:MAP_get_ptr(Map:map, Pointer:key_ptr)
{
    new Pointer:ret = MEM_NULLPTR, Map:found_map = MAP_find(map, key_ptr);
    if (found_map != MAP_NULL)
    {
        ret = Pointer:MEM_get_val(Pointer:found_map, _:MAP_struct_value_ptr);
    }
    return ret;
}

// Map find minimum
static stock Map:MAP_find_minimum(Map:map)
{
    new Map:ret = map, Map:m = map;
    while (m != MAP_NULL)
    {
        m = Map:MEM_get_val(Pointer:m, _:MAP_struct_left);
        if (m != MAP_NULL)
        {
            ret = m;
        }
    }
    return ret;
}

// Map remove found
static stock MAP_remove_found(&Map:parent_map, Map:found_map)
{
    new m[MAP_struct], pm[MAP_struct], bool:hp;
    MEM_get_arr(Pointer:found_map, _, m);
    hp = (m[MAP_struct_parent] != MAP_NULL);
    if (hp)
    {
        MEM_get_arr(Pointer:m[MAP_struct_parent], _, pm);
    }
    if (m[MAP_struct_left] == MAP_NULL)
    {
        if (m[MAP_struct_right] == MAP_NULL)
        {
            // Case 1
            if (hp)
            {
                if (pm[MAP_struct_left] == found_map)
                {
                    MEM_set_val(Pointer:m[MAP_struct_parent], _:MAP_struct_left, _:MAP_NULL);
                }
                else
                {
                    MEM_set_val(Pointer:m[MAP_struct_parent], _:MAP_struct_right, _:MAP_NULL);
                }
            }
            else
            {
                parent_map = MAP_NULL;
            }
            MEM_delete(m[MAP_struct_key_ptr]);
            MEM_delete(m[MAP_struct_value_ptr]);
            MEM_delete(Pointer:found_map);
        }
        else
        {
            // Case 2 (right)
            if (hp)
            {
                if (pm[MAP_struct_left] == found_map)
                {
                    MEM_set_val(Pointer:m[MAP_struct_parent], _:MAP_struct_left, _:m[MAP_struct_right]);
                }
                else
                {
                    MEM_set_val(Pointer:m[MAP_struct_parent], _:MAP_struct_right, _:m[MAP_struct_right]);
                }
            }
            else
            {
                parent_map = m[MAP_struct_right];
            }
            MEM_set_val(Pointer:m[MAP_struct_right], _:MAP_struct_parent, _:m[MAP_struct_parent]);
            MEM_delete(m[MAP_struct_key_ptr]);
            MEM_delete(m[MAP_struct_value_ptr]);
            MEM_delete(Pointer:found_map);
        }
    }
    else
    {
        if (m[MAP_struct_right] == MAP_NULL)
        {
            // Case 2 (left)
            if (hp)
            {
                if (pm[MAP_struct_left] == found_map)
                {
                    MEM_set_val(Pointer:m[MAP_struct_parent], _:MAP_struct_left, _:m[MAP_struct_left]);
                }
                else
                {
                    MEM_set_val(Pointer:m[MAP_struct_parent], _:MAP_struct_right, _:m[MAP_struct_left]);
                }
            }
            else
            {
                parent_map = m[MAP_struct_left];
            }
            MEM_set_val(Pointer:m[MAP_struct_left], _:MAP_struct_parent, _:m[MAP_struct_parent]);
            MEM_delete(m[MAP_struct_key_ptr]);
            MEM_delete(m[MAP_struct_value_ptr]);
            MEM_delete(Pointer:found_map);
        }
        else
        {
            // Case 3
            new Map:min_map = MAP_find_minimum(m[MAP_struct_right]), mm[MAP_struct], Pointer:key_ptr;
            MEM_get_arr(Pointer:min_map, _, mm);
            key_ptr = MEM_clone(mm[MAP_struct_key_ptr]);
            if (key_ptr != MEM_NULLPTR)
            {
                new Pointer:value_ptr = MEM_clone(mm[MAP_struct_value_ptr]);
                if (value_ptr == MEM_NULLPTR)
                {
                    MEM_delete(key_ptr);
                }
                else
                {
                    MEM_delete(m[MAP_struct_key_ptr]);
                    MEM_delete(m[MAP_struct_value_ptr]);
                    MEM_set_val(Pointer:found_map, _:MAP_struct_key_hash, m[MAP_struct_key_hash]);
                    MEM_set_val(Pointer:found_map, _:MAP_struct_key_ptr, _:key_ptr);
                    MEM_set_val(Pointer:found_map, _:MAP_struct_value_ptr, _:value_ptr);
                    MAP_remove_found(parent_map, min_map);
                }
            }
        }
    }
}

// Map remove
static stock MAP_remove(&Map:map, Pointer:key_ptr)
{
    new Map:fm = MAP_find(map, key_ptr);
    if (fm != MAP_NULL)
    {
        MAP_remove_found(Map:map, fm);
    }
}

// Map insert (key, value)
stock MAP_insert_val_val(&Map:map, key, value)
{
    new Pointer:k = MEM_new_val(key);
    if (k != MEM_NULLPTR)
    {
        new Pointer:v = MEM_new_val(value);
        if (v != MEM_NULLPTR)
        {
            MAP_insert(map, k, v);
            MEM_delete(v);
        }
        MEM_delete(k);
    }
}

// Map insert (key, value[])
stock MAP_insert_val_arr(&Map:map, key, const value[], value_size = sizeof value)
{
    if (value_size > 0)
    {
        new Pointer:k = MEM_new_val(key);
        if (k != MEM_NULLPTR)
        {
            new Pointer:v = MEM_new_arr(value, value_size);
            if (v != MEM_NULLPTR)
            {
                MAP_insert(map, k, v);
                MEM_delete(v);
            }
            MEM_delete(k);
        }
    }
}

// Map insert (key[], value)
stock MAP_insert_arr_val(&Map:map, const key[], key_size = sizeof key, value)
{
    if (key_size > 0)
    {
        new Pointer:k = MEM_new_arr(key, key_size);
        if (k != MEM_NULLPTR)
        {
            new Pointer:v = MEM_new_val(value);
            if (v != MEM_NULLPTR)
            {
                MAP_insert(map, k, v);
                MEM_delete(v);
            }
            MEM_delete(k);
        }
    }
}

// Map insert (key[], value[])
stock MAP_insert_arr_arr(&Map:map, const key[], key_size = sizeof key, const value[], value_size = sizeof value)
{
    if ((value_size > 0) && (key_size > 0))
    {
        new Pointer:k = MEM_new_arr(key, key_size);
        if (k != MEM_NULLPTR)
        {
            new Pointer:v = MEM_new_arr(value, value_size);
            if (v != MEM_NULLPTR)
            {
                MAP_insert(map, k, v);
                MEM_delete(v);
            }
            MEM_delete(k);
        }
    }
}

// Map insert (key, value[] as string)
stock MAP_insert_val_str(&Map:map, key, const value[])
{
    MAP_insert_val_arr(map, key, value, strlen(value) + 1);
}

// Map insert (key[], value[] as string)
stock MAP_insert_arr_str(&Map:map, const key[], key_size = sizeof key, const value[])
{
    MAP_insert_arr_arr(map, key, key_size, value, strlen(value) + 1);
}

// Map insert (key[] as string, value[] as string)
stock MAP_insert_str_str(&Map:map, const key[], const value[])
{
    MAP_insert_arr_arr(map, key, strlen(key) + 1, value, strlen(value) + 1);
}

// Map insert (key[] as string, value)
stock MAP_insert_str_val(&Map:map, const key[], value)
{
    MAP_insert_arr_val(map, key, strlen(key) + 1, value);
}

// Map insert (key[] as string, value)
stock MAP_insert_str_arr(&Map:map, const key[], const value[], value_size = sizeof value)
{
    MAP_insert_arr_arr(map, key, strlen(key) + 1, value, value_size);
}

// Map get pointer (key)
stock Pointer:MAP_get_ptr_val(Map:map, key)
{
    new Pointer:ret = MEM_NULLPTR;
    if (map != MAP_NULL)
    {
        new Pointer:key_ptr = MEM_new_val(key);
        if (key_ptr != MEM_NULLPTR)
        {
            ret = MAP_get_ptr(map, key_ptr);
            MEM_delete(key_ptr);
        }
    }
    return ret;
}

// Map get pointer (key[])
stock Pointer:MAP_get_ptr_arr(Map:map, const key[], key_size = sizeof key)
{
    new Pointer:ret = MEM_NULLPTR;
    if ((map != MAP_NULL) && (key_size > 0))
    {
        new Pointer:key_ptr = MEM_new_arr(key, key_size);
        if (key_ptr != MEM_NULLPTR)
        {
            ret = MAP_get_ptr(map, key_ptr);
            MEM_delete(key_ptr);
        }
    }
    return ret;
}

// Map get pointer (key[] as string)
stock Pointer:MAP_get_ptr_str(Map:map, const key[])
{
    return MAP_get_ptr_arr(map, key, strlen(key) + 1);
}

// Map contains (key)
stock bool:MAP_contains_val(Map:map, key)
{
    new bool:ret = false;
    if (map != MAP_NULL)
    {
        new Pointer:key_ptr = MEM_new_val(key);
        if (key_ptr != MEM_NULLPTR)
        {
            ret = (MAP_find(map, key_ptr) != MAP_NULL);
            MEM_delete(key_ptr);
        }
    }
    return ret;
}

// Map contains (key[])
stock bool:MAP_contains_arr(Map:map, const key[], key_size = sizeof key)
{
    new bool:ret = false;
    if ((map != MAP_NULL) && (key_size > 0))
    {
        new Pointer:key_ptr = MEM_new_arr(key, key_size);
        if (key_ptr != MEM_NULLPTR)
        {
            ret = (MAP_find(map, key_ptr) != MAP_NULL);
            MEM_delete(key_ptr);
        }
    }
    return ret;
}

// Map contains (key[] as string)
stock bool:MAP_contains_str(Map:map, const key[])
{
    return MAP_contains_arr(map, key, strlen(key) + 1);
}

// Map get value (key)
stock MAP_get_val_val(Map:map, key)
{
    return MEM_get_val(MAP_get_ptr_val(map, key));
}

// Map get array (key)
stock MAP_get_val_arr(Map:map, key, value[], value_size = sizeof value)
{
    new Pointer:ptr = MAP_get_ptr_val(map, key), v_sz = MEM_get_size(ptr);
    MEM_get_arr(ptr, _, value, (v_sz < value_size) ? v_sz : value_size);
}

// Map get value (key[])
stock MAP_get_arr_val(Map:map, const key[], key_size = sizeof key)
{
    return MEM_get_val(MAP_get_ptr_arr(map, key, key_size));
}

// Map get array (key[])
stock MAP_get_arr_arr(Map:map, const key[], key_size = sizeof key, value[], value_size = sizeof value)
{
    new Pointer:ptr = MAP_get_ptr_arr(map, key, key_size), v_sz = MEM_get_size(ptr);
    MEM_get_arr(ptr, _, value, (v_sz < value_size) ? v_sz : value_size);
}

// Map get value (key[] as string)
stock MAP_get_str_val(Map:map, const key[])
{
    return MAP_get_arr_val(map, key, strlen(key) + 1);
}

// Map get array (key[] as string)
stock MAP_get_str_arr(Map:map, const key[], value[], value_size = sizeof value)
{
    MAP_get_arr_arr(map, key, strlen(key) + 1, value, value_size);
}

// Count the nodes in `map`
stock MAP_count(Map:map)
{
    new ret;
    if (map != MAP_NULL)
    {
        new m[MAP_struct];
        MEM_get_arr(Pointer:map, _, m);
        ret = 1;
        ret += MAP_count(m[MAP_struct_left]);
        ret += MAP_count(m[MAP_struct_right]);
    }
    return ret;
}

// Map remove (key)
stock MAP_remove_val(&Map:map, key)
{
    if (map != MAP_NULL)
    {
        new Pointer:key_ptr = MEM_new_val(key);
        if (key_ptr != MEM_NULLPTR)
        {
            MAP_remove(map, key_ptr);
            MEM_delete(key_ptr);
        }
    }
}

// Map remove (key[])
stock MAP_remove_arr(&Map:map, const key[], key_size = sizeof key)
{
    if ((map != MAP_NULL) && (key_size > 0))
    {
        new Pointer:key_ptr = MEM_new_arr(key, key_size);
        if (key_ptr != MEM_NULLPTR)
        {
            MAP_remove(map, key_ptr);
            MEM_delete(key_ptr);
        }
    }
}

// Map remove (key[] as string)
stock MAP_remove_str(&Map:map, const key[])
{
    MAP_remove_arr(map, key, strlen(key) + 1);
}

// Clear map
stock MAP_clear(&Map:map)
{
    if (map != MAP_NULL)
    {
        new m[MAP_struct];
        MEM_get_arr(Pointer:map, _, m);
        MAP_clear(m[MAP_struct_left]);
        MAP_clear(m[MAP_struct_right]);
        MEM_delete(m[MAP_struct_key_ptr]);
        MEM_delete(m[MAP_struct_value_ptr]);
        MEM_delete(Pointer:map);
        map = MAP_NULL;
    }
}

// Map iterator get
stock Map:MAP_iter_get(Map:map, &Pointer:key_ptr, &Pointer:value_ptr)
{
    if (map != MAP_NULL)
    {
        new m[MAP_struct];
        MEM_get_arr(Pointer:map, _, m);
        key_ptr = m[MAP_struct_key_ptr];
        value_ptr = m[MAP_struct_value_ptr];
    }
    return map;
}

// Map iterator next
stock Map:MAP_iter_next(Map:map, Map:invoker, &Pointer:key_ptr, &Pointer:value_ptr)
{
    new Map:ret = MAP_NULL;
    if (map != MAP_NULL)
    {
        new m[MAP_struct];
        MEM_get_arr(Pointer:map, _, m);
        if (m[MAP_struct_left] != MAP_NULL)
        {
            ret =
                ((invoker == m[MAP_struct_left])
                    ? ((m[MAP_struct_right] != MAP_NULL)
                        ? MAP_iter_get(m[MAP_struct_right], key_ptr, value_ptr)
                        : MAP_iter_next(m[MAP_struct_parent], map, key_ptr, value_ptr))
                    : ((m[MAP_struct_right] != MAP_NULL)
                    ? ((invoker == m[MAP_struct_right])
                        ? MAP_iter_next(m[MAP_struct_parent], map, key_ptr, value_ptr)
                        : MAP_iter_get(m[MAP_struct_left], key_ptr, value_ptr))
                    : MAP_iter_get(m[MAP_struct_left], key_ptr, value_ptr)))
            ;
        }
        else if (m[MAP_struct_right] != MAP_NULL)
        {
            ret =
                (invoker == m[MAP_struct_right])
                    ? MAP_iter_next(m[MAP_struct_parent], map, key_ptr, value_ptr)
                    : MAP_iter_get(m[MAP_struct_right], key_ptr, value_ptr)
            ;
        }
        else
        {
            ret = MAP_iter_next(m[MAP_struct_parent], map, key_ptr, value_ptr);
        }
    }
    return ret;
}
