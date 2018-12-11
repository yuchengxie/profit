#include "profit.hpp"

void profit::bet(name player, name referrer, const asset &bet)
{
    print("bet...", player, "\n");
    eosio_assert(bet.symbol == EOS_SYMBOL, "only core token allowed");
    eosio_assert(bet.is_valid(), "invalid amount");
    eosio_assert(bet.amount > 0, "bet must positive quantity");
    require_auth(player);
    auto cur_player_itr = _accounts.find(1);
    eosio_assert(cur_player_itr != _accounts.end(), "unknow account");

    //transfer platform currency
    // transaction out{};
    // out.actions.emplace_back(permission_level{_self, "active"_n}, "eosio.token"_n, "transfer"_n, std::make_tuple("TEST"));
    // out.send("TEST", _self);
}

void profit::stake(name user, asset &amount)
{
    print("stake...", user, "\n");
}

void profit::unstake(name user, asset &amount)
{
    print("unstake...", user, "\n");
}

void profit::claim(name user)
{
    
}

EOSIO_DISPATCH(profit, (bet)(stake)(unstake))
