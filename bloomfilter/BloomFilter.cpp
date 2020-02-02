#include <iostream>
#include <cstdlib>

#include "BloomFilter.h"

using namespace std;

BloomFilter::BloomFilter(unsigned int m, unsigned int k):
    _m(m), _k(k) {
        //vector按照m大小重新分配内存
        table.resize(_m);
        //默认都是0 
        for(int i = 0; i < _m; ++i)
            table[i] = false;
}

unsigned int BloomFilter::getSeed(unsigned int hash_index) {
    string seed = "13";
    for(int i = 0; i < hash_index; ++i)
        seed += (i % 2 == 0)? "1" : "3";

    //种子是一个整型
    return atoi(seed.c_str());
}

unsigned int BloomFilter::BKDR_Hash(string s, unsigned int hash_index) {
    const char *ps = s.c_str();
    unsigned int seed = getSeed(hash_index);
    unsigned int hash = 0;

    for(int i = 0; i < s.size(); ++i)
        hash += hash * seed + ps[i];

    //hash的计算方法主要是取余
    return hash % _m;
}

//插入字符串s的时候，计算k种hash值，填充bitset
void BloomFilter::insertElement(string s) {
    for(int i = 0; i < _k; ++i) {
        unsigned int index = BKDR_Hash(s, i);
        // cout << index << endl;
        table[index] = true;
    }
}

bool BloomFilter::existsElement(string s) {
    for(int i = 0; i < _k; ++i) {
        unsigned int index = BKDR_Hash(s, i);
        //只有所有k个都是true，才返回true
        if(!table[index])
            return false;
    }
    return true;
}
