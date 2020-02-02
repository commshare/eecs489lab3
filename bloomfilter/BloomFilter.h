#ifndef __BLOOM_FILTER_H__
#define __BLOOM_FILTER_H__

#include <vector>
#include <string>

class BloomFilter {
    public:
        BloomFilter(unsigned int m, unsigned int k);
        //只有插入和查询两种可能
        void insertElement(std::string s);
        bool existsElement(std::string s);
    private:
        unsigned int BKDR_Hash(std::string s, unsigned int i);
        unsigned int getSeed(unsigned int hash_index);
        std::vector<bool> table;//代表一个bitset，只有0和1两种可能，正好用bool
        //bitset之后m个元素
        unsigned int _m;
        //k种hash方法
        unsigned int _k; 
};

#endif // __BLOOM_FILTER_H__
