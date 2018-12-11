#include <eosiolib/crypto.h>
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/transaction.hpp>
#include <string>
#define EOS_SYMBOL symbol("EOS", 4)
using namespace eosio;

class profit : public eosio::contract
{
  public:
    using contract::contract;

    profit(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds),
                                                                    _pool(_code, _code.value),
                                                                    _stake(_code, _code.value),
                                                                    _accounts(_code, _code.value){}

                                                                        [[eosio::action]] void bet(name player, name referrer, const asset &bet);
    [[eosio::action]] void stake(name user, uint64_t amount);
    [[eosio::action]] void unstake(name user, uint64_t amount);

  public:
    struct [[eosio::table]] pool
    {
        uint64_t current_id;
        uint64_t total_eos_balance; //分红池累计
        uint64_t primary_key() const { return current_id; }
    };
    struct [[eosio::table]] stakes
    {
        uint64_t current_id;
        uint64_t total_stake; //总共质押
        uint64_t unstake;     //未质押
        uint64_t stake;       //已质押
        uint64_t rate;        //收益比例
        uint64_t primary_key() const { return current_id; }
    };
    struct [[eosio::table]] account
    {
        uint64_t id;
        name account;
        asset balance;
        int64_t primary_key() const { return id; }
    };

    typedef eosio::multi_index<"pool"_n, pool> pool_index;
    typedef eosio::multi_index<"stake"_n, stakes> stake_index;
    typedef eosio::multi_index<"mybalance"_n, account> account_index;
    pool_index _pool;
    stake_index _stake;
    account_index _accounts;
};
