/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <map>
#include <string>

#include "base/containers/contains.h"
#include "brave/components/brave_wallet/browser/brave_wallet_constants.h"
#include "brave/components/brave_wallet/common/brave_wallet.mojom-shared.h"

namespace brave_wallet {

const std::vector<mojom::BlockchainToken>& GetWyreBuyTokens() {
  static base::NoDestructor<std::vector<mojom::BlockchainToken>> tokens(
      {{"", "Avalanche", "", false, false, false, "AVAX", 18, true, "", "",
        mojom::kAvalancheMainnetChainId, mojom::CoinType::ETH},
       {"0x0D8775F648430679A709E98d2b0Cb6250d2887EF", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"", "Ethereum", "", false, false, false, "ETH", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0xA0b86991c6218b36c1d19D4a2e9Eb0cE3606eB48", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x6B175474E89094C44Da98b954EedeAC495271d0F", "DAI", "dai.png", true,
        false, false, "DAI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x7Fc66500c84A76Ad7e9c93437bFc5Ac33E2DDaE9", "AAVE", "AAVE.png", true,
        false, false, "AAVE", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x4Fabb145d64652a948d72533023f6E7A623C7C53", "Binance USD", "busd.png",
        true, false, false, "BUSD", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xc00e94cb662c3520282e6f5717214004a7f26888", "Compound", "comp.png",
        true, false, false, "COMP", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xD533a949740bb3306d119CC777fa900bA034cd52", "Curve", "curve.png",
        true, false, false, "CRV", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xbf0f3ccb8fa385a287106fba22e6bb722f94d686", "Digital USD", "", true,
        false, false, "ZUSD", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x056Fd409E1d7A124BD7017459dFEa2F387b6d5Cd", "Gemini Dollar",
        "gusd.png", true, false, false, "GUSD", 2, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0xC08512927D12348F6620a698105e1BAac6EcD911", "Digital JPY", "", true,
        false, false, "GYEN", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x514910771AF9Ca656af840dff83E8264EcF986CA", "Chainlink",
        "chainlink.png", true, false, false, "LINK", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x9f8F72aA9304c8B593d555F12eF6589cC3A579A2", "Maker", "mkr.png", true,
        false, false, "MKR", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xC011a73ee8576Fb46F5E1c5751cA3B9Fe0af2a6F", "Synthetix",
        "synthetix.png", true, false, false, "SNX", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x04Fa0d235C4abf4BcF4787aF4CF447DE572eF828", "UMA", "UMA.png", true,
        false, false, "UMA", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x1f9840a85d5aF5bf1D1762F925BDADdC4201F984", "Uniswap", "uni.png",
        true, false, false, "UNI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x2791Bca1f2de4661ED88A30C99A7a9449Aa84174", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0xB97EF9Ef8734C71904D8002F8b6Bc66Dd9c48a6E", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kAvalancheMainnetChainId, mojom::CoinType::ETH},
       {"0x8e870d67f660d95d5be530380d0ec0bd388289e1", "Pax Dollar", "usdp.png",
        true, false, false, "PAX", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Polygon", "", false, false, false, "MATIC", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0xA4Bdb11dc0a2bEC88d24A3aa1E6Bb17201112eBe", "Stably Dollar",
        "usds.png", true, false, false, "USDS", 6, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0xdAC17F958D2ee523a2206206994597C13D831ec7", "Tether", "usdt.png",
        true, false, false, "USDT", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x2260FAC5E5542a773Aa44fBCfeDf7C193bc2C599", "Wrapped Bitcoin",
        "wbtc.png", true, false, false, "WBTC", 8, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x0bc529c00C6401aEF6D220BE8C6Ea1667F6Ad93e", "Yearn.Finance",
        "yfi.png", true, false, false, "YFI", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x9043d4d51C9d2e31e3F169de4551E416970c27Ef", "Palm DAI", "pdai.png",
        true, false, false, "PDAI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x03ab458634910AaD20eF5f1C8ee96F1D6ac54919", "Rai Reflex Index",
        "rai.png", true, false, false, "RAI", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH}});
  return *tokens;
}

const std::vector<mojom::BlockchainToken>& GetRampBuyTokens() {
  static base::NoDestructor<std::vector<mojom::BlockchainToken>> tokens(
      {{"", "Ethereum", "", false, false, false, "ETH", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"", "BNB", "", true, false, false, "BNB", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"", "Avalanche", "", false, false, false, "AVAX", 18, true, "", "",
        mojom::kAvalancheMainnetChainId, mojom::CoinType::ETH},
       {"", "Filecoin", "", false, false, false, "FIL", 18, true, "", "",
        mojom::kFilecoinMainnet, mojom::CoinType::FIL},
       {"", "Celo", "", false, false, false, "CELO", 18, true, "", "",
        mojom::kCeloMainnetChainId, mojom::CoinType::ETH},
       {"0xD8763CBa276a3738E6DE85b4b3bF5FDed6D6cA73", "Celo Euro", "ceur.png",
        true, false, false, "CEUR", 18, true, "", "",
        mojom::kCeloMainnetChainId, mojom::CoinType::ETH},
       {"0x765DE816845861e75A25fCA122bb6898B8B1282a", "Celo Dollar", "cusd.png",
        true, false, false, "CUSD", 18, true, "", "",
        mojom::kCeloMainnetChainId, mojom::CoinType::ETH},
       {"0x6b175474e89094c44da98b954eedeac495271d0f", "DAI Stablecoin",
        "dai.png", true, false, false, "DAI", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"", "Ethereum", "", false, false, false, "ETH", 18, true, "", "",
        mojom::kOptimismMainnetChainId, mojom::CoinType::ETH},
       {"", "Polygon", "", false, false, false, "MATIC", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x8f3cf7ad23cd3cadbd9735aff958023239c6a063", "DAI Stablecoin",
        "dai.png", true, false, false, "DAI", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x7ceB23fD6bC0adD59E62ac25578270cFf1b9f619", "Ethereum", "eth.png",
        true, false, false, "ETH", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0xbbba073c31bf03b8acf7c28ef0738decf3695683", "Sandbox", "sand.png",
        true, false, false, "SAND", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x0f5d2fb29fb7d3cfee444a200298f468908cc942", "Decentraland",
        "mana.png", true, false, false, "MANA", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0xa1c57f48f0deb89f569dfbe6e2b7f46d33606fd4", "Decentraland",
        "mana.png", true, false, false, "MANA", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x2791bca1f2de4661ed88a30c99a7a9449aa84174", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x3Cef98bb43d732E2F285eE605a8158cDE967D219", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"", "Solana", "", false, false, false, "SOL", 9, true, "", "",
        mojom::kSolanaMainnet, mojom::CoinType::SOL},
       {"EPjFWdd5AufqSSqeM2qN1xzybapC8G4wEGGkZwyTDt1v", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "", mojom::kSolanaMainnet,
        mojom::CoinType::SOL},
       {"Es9vMFrzaCERmJfrF4H2FYD4KCoNkY11McCe8BenwNYB", "Tether", "usdt.png",
        false, false, false, "USDT", 6, true, "", "", mojom::kSolanaMainnet,
        mojom::CoinType::SOL},
       {"0xdac17f958d2ee523a2206206994597c13d831ec7", "Tether", "usdt.png",
        true, false, false, "USDT", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xa0b86991c6218b36c1d19d4a2e9eb0ce3606eb48", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x0d8775f648430679a709e98d2b0cb6250d2887ef", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"EPeUFDgHRxs9xxEPVaL6kfGQvCon7jmAWKVUHuux1Tpz", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kSolanaMainnet, mojom::CoinType::SOL}});
  return *tokens;
}

const std::vector<mojom::BlockchainToken>& GetSardineBuyTokens() {
  static base::NoDestructor<std::vector<mojom::BlockchainToken>> tokens(
      {{"", "Ethereum", "", false, false, false, "ETH", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x7Fc66500c84A76Ad7e9c93437bFc5Ac33E2DDaE9", "AAVE", "aave.png", true,
        false, false, "AAVE", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x7Fc66500c84A76Ad7e9c93437bFc5Ac33E2DDaE9", "AAVE", "aave.png", true,
        false, false, "AAVE", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Avalanche", "", false, false, false, "AVAX", 18, true, "", "",
        mojom::kAvalancheMainnetChainId, mojom::CoinType::ETH},
       {"0x0d8775f648430679a709e98d2b0cb6250d2887ef", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x4Fabb145d64652a948d72533023f6E7A623C7C53", "Binance USD", "BUSD.png",
        true, false, false, "BUSD", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x4Fabb145d64652a948d72533023f6E7A623C7C53", "Binance USD", "busd.png",
        true, false, false, "BUSD", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xc00e94cb662c3520282e6f5717214004a7f26888", "Compound", "comp.png",
        true, false, false, "COMP", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x6B175474E89094C44Da98b954EedeAC495271d0F", "DAI", "dai.png", true,
        false, false, "DAI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x0f5d2fb29fb7d3cfee444a200298f468908cc942", "Decentraland",
        "mana.png", true, false, false, "MANA", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0xf629cbd94d3791c9250152bd8dfbdf380e2a3b9c", "Enjin Coin", "enj.png",
        true, false, false, "ENJ", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Fantom", "", false, false, false, "FTM", 18, true, "", "",
        mojom::kFantomMainnetChainId, mojom::CoinType::ETH},
       {"0xdeFA4e8a7bcBA345F687a2f1456F5Edd9CE97202", "Kyber Network",
        "kyber.png", true, false, false, "KNC", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x9f8F72aA9304c8B593d555F12eF6589cC3A579A2", "Maker", "mkr.png", true,
        false, false, "MKR", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xd26114cd6ee289accf82350c8d8487fedb8a0c07", "OMG Network", "omg.png",
        true, false, false, "OMG", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Polygon", "", false, false, false, "MATIC", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x7D1AfA7B718fb893dB30A3aBc0Cfc608AaCfeBB0", "Polygon", "matic.png",
        false, false, false, "MATIC", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x45804880de22913dafe09f4980848ece6ecbaf78", "Pax Gold", "paxg.png",
        true, false, false, "PAXG", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x8e870d67f660d95d5be530380d0ec0bd388289e1", "Pax Dollar", "usdp.png",
        true, false, false, "PAX", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x95ad61b0a150d79219dcf64e1e6cc01f0b64c4ce", "Shiba Inu", "shib.png",
        true, false, false, "SHIB", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Solana", "", false, false, false, "SOL", 9, true, "", "",
        mojom::kSolanaMainnet, mojom::CoinType::SOL},
       {"0xdAC17F958D2ee523a2206206994597C13D831ec7", "Tether", "usdt.png",
        true, false, false, "USDT", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xc944e90c64b2c07662a292be6244bdf05cda44a7", "The Graph",
        "graphToken.png", true, false, false, "GRT", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x0000000000085d4780b73119b644ae5ecd22b376", "TrueUSD", "tusd.png",
        true, false, false, "TUSD", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x0000000000085d4780B73119b644AE5ecd22b376", "The Sandbox", "sand.png",
        true, false, false, "SAND", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x1f9840a85d5aF5bf1D1762F925BDADdC4201F984", "Uniswap", "uni.png",
        true, false, false, "UNI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xA0b86991c6218b36c1d19D4a2e9Eb0cE3606eB48", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xe41d2489571d322189246dafa5ebde1f4699f498", "Ox", "zrx.png", true,
        false, false, "ZRX", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xbb0e17ef65f82ab018d8edd776e8dd940327b28b", "Axie Infinity",
        "axs.png", true, false, false, "AXS", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH}});
  return *tokens;
}

const std::vector<mojom::BlockchainToken>& GetTransakBuyTokens() {
  static base::NoDestructor<std::vector<mojom::BlockchainToken>> tokens(
      {{"", "Ethereum", "", false, false, false, "ETH", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"", "Ethereum", "", false, false, false, "ETH", 18, true, "", "",
        mojom::kOptimismMainnetChainId, mojom::CoinType::ETH},
       {"0xdAC17F958D2ee523a2206206994597C13D831ec7", "Tether", "usdt.png",
        true, false, false, "USDT", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Ethereum", "", false, false, false, "ETH", 18, true, "", "",
        mojom::kArbitrumMainnetChainId, mojom::CoinType::ETH},
       {"0xc2132D05D31c914a87C6611C10748AEb04B58e8F", "Tether", "usdt.png",
        true, false, false, "USDT", 6, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"Es9vMFrzaCERmJfrF4H2FYD4KCoNkY11McCe8BenwNYB", "Tether", "usdt.png",
        false, false, false, "USDT", 6, true, "", "", mojom::kSolanaMainnet,
        mojom::CoinType::SOL},
       {"", "BNB", "", false, false, false, "BNB", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x1f9840a85d5aF5bf1D1762F925BDADdC4201F984", "Uniswap", "uni.png",
        true, false, false, "UNI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xA0b86991c6218b36c1d19D4a2e9Eb0cE3606eB48", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x2791bca1f2de4661ed88a30c99a7a9449aa84174", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"EPjFWdd5AufqSSqeM2qN1xzybapC8G4wEGGkZwyTDt1v", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "", mojom::kSolanaMainnet,
        mojom::CoinType::SOL},
       {"0xB97EF9Ef8734C71904D8002F8b6Bc66Dd9c48a6E", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kAvalancheMainnetChainId, mojom::CoinType::ETH},
       {"0x8ac76a51cc950d9822d68b83fe1ad97b32cd580d", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x7F5c764cBc14f9669B88837ca1490cCa17c31607", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kOptimismMainnetChainId, mojom::CoinType::ETH},
       {"0xFF970A61A04b1cA14834A43f5dE4533eBDDB5CC8", "USD Coin", "usdc.png",
        true, false, false, "USDC", 6, true, "", "",
        mojom::kArbitrumMainnetChainId, mojom::CoinType::ETH},
       {"0x514910771AF9Ca656af840dff83E8264EcF986CA", "Chainlink",
        "chainlink.png", true, false, false, "LINK", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x1bfd67037b42cf73acf2047067bd4f2c47d9bfd6", "Wrapped Bitcoin",
        "wbtc.png", true, false, false, "WBTC", 8, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x2260FAC5E5542a773Aa44fBCfeDf7C193bc2C599", "Wrapped Bitcoin",
        "wbtc.png", true, false, false, "WBTC", 8, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"", "Solana", "", false, false, false, "SOL", 9, true, "", "",
        mojom::kSolanaMainnet, mojom::CoinType::SOL},
       {"0xae7ab96520DE3A18E5e111B5EaAb095312D7fE84", "Lido Staked Ether",
        "steth.png", true, false, false, "STETH", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"", "Polygon", "", false, false, false, "MATIC", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x6B175474E89094C44Da98b954EedeAC495271d0F", "DAI", "dai.png", true,
        false, false, "DAI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x8f3cf7ad23cd3cadbd9735aff958023239c6a063", "DAI Stablecoin",
        "dai.png", true, false, false, "DAI", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x4Fabb145d64652a948d72533023f6E7A623C7C53", "Binance USD", "busd.png",
        true, false, false, "BUSD", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x7Fc66500c84A76Ad7e9c93437bFc5Ac33E2DDaE9", "AAVE", "aave.png", true,
        false, false, "AAVE", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xd6df932a45c0f255f85145f286ea0b292b21c90b", "AAVE", "aave.png", true,
        false, false, "AAVE", 18, true, "", "", mojom::kPolygonMainnetChainId,
        mojom::CoinType::ETH},
       {"0x4d224452801ACEd8B2F0aebE155379bb5D594381", "ApeCoin", "ape.png",
        true, false, false, "APE", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x3845badade8e6dff049820680d1f14bd3903a5d0", "The Sandbox", "sand.png",
        true, false, false, "SAND", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Avalanche", "", false, false, false, "AVAX", 18, true, "", "",
        mojom::kAvalancheMainnetChainId, mojom::CoinType::ETH},
       {"0x0f5d2fb29fb7d3cfee444a200298f468908cc942", "Decentraland",
        "mana.png", true, false, false, "MANA", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0xa1c57f48f0deb89f569dfbe6e2b7f46d33606fd4", "Decentraland",
        "mana.png", true, false, false, "MANA", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x0b3f868e0be5597d5db7feb59e1cadbb0fdda50a", "Sushi", "sushi.png",
        true, false, false, "SUSHI", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x0b3f868e0be5597d5db7feb59e1cadbb0fdda50a", "Sushi", "sushi.png",
        true, false, false, "SUSHI", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x6B3595068778DD592e39A122f4f5a5cF09C90fE2", "Sushi", "sushi.png",
        true, false, false, "SUSHI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x9f8F72aA9304c8B593d555F12eF6589cC3A579A2", "Maker", "mkr.png", true,
        false, false, "MKR", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Celo", "", false, false, false, "CELO", 18, true, "", "",
        mojom::kCeloMainnetChainId, mojom::CoinType::ETH},
       {"0xf629cbd94d3791c9250152bd8dfbdf380e2a3b9c", "Enjin Coin", "enj.png",
        true, false, false, "ENJ", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x0D8775F648430679A709E98d2b0Cb6250d2887EF", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"EPeUFDgHRxs9xxEPVaL6kfGQvCon7jmAWKVUHuux1Tpz", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kSolanaMainnet, mojom::CoinType::SOL},
       {"0x0D8775F648430679A709E98d2b0Cb6250d2887EF", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x3Cef98bb43d732E2F285eE605a8158cDE967D219", "Basic Attention Token",
        "bat.png", true, false, false, "BAT", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"", "Fantom", "", false, false, false, "FTM", 18, true, "", "",
        mojom::kFantomMainnetChainId, mojom::CoinType::ETH},
       {"0x72d6066F486bd0052eefB9114B66ae40e0A6031a", "WazirX", "wrx.png", true,
        false, false, "WRX", 8, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x111111111117dC0aa78b770fA6A738034120C302", "1Inch", "1inch.png",
        true, false, false, "1INCH", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xc00e94cb662c3520282e6f5717214004a7f26888", "Compound", "comp.png",
        true, false, false, "COMP", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x7dd9c5cba05e151c895fde1cf355c9a1d5da6429", "Golem", "glm.png", true,
        false, false, "GLM", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xC581b735A1688071A1746c968e0798D642EDE491", "Euro Tether", "eurt.png",
        true, false, false, "EURT", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x12b6893ce26ea6341919fe289212ef77e51688c8", "Tamadoge", "tama.png",
        true, false, false, "TAMA", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xf411903cbc70a74d22900a5de66a2dda66507255", "Verasity", "vra.png",
        true, false, false, "VRA", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x3a4f40631a4f906c2BaD353Ed06De7A5D3fCb430", "PlayDapp", "pla.png",
        true, false, false, "PLA", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x8765f05ADce126d70bcdF1b0a48Db573316662eB", "PlayDapp", "pla.png",
        true, false, false, "PLA", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x69af81e73a73b40adf4f3d4223cd9b1ece623074", "Mask Network",
        "MASK.png", true, false, false, "MASK", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x69af81e73a73b40adf4f3d4223cd9b1ece623074", "Mask Network",
        "mask.png", true, false, false, "MASK", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x4b0f1812e5df2a09796481ff14017e6005508003", "Trust Wallet", "twt.png",
        true, false, false, "TWT", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x491604c0fdf08347dd1fa4ee062a822a5dd06b5d", "Cartesi", "ctsi.png",
        true, false, false, "CTSI", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"", "Aurora", "aurora.png", false, false, false, "AURORA", 18, true, "",
        "", mojom::kAuroraMainnetChainId, mojom::CoinType::ETH},
       {"0x83e6f1E41cdd28eAcEB20Cb649155049Fac3D5Aa", "Polkastarter",
        "pols.png", true, false, false, "POLS", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x83e6f1E41cdd28eAcEB20Cb649155049Fac3D5Aa", "Polkastarter",
        "pols.png", true, false, false, "POLS", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x6e84a6216ea6dacc71ee8e6b0a5b7322eebc0fdd", "Joe", "joe.png", true,
        false, false, "JOE", 18, true, "", "", mojom::kAvalancheMainnetChainId,
        mojom::CoinType::ETH},
       {"0xCa3F508B8e4Dd382eE878A314789373D80A5190A", "Beefy.Finance",
        "bifi.png", true, false, false, "BIFI", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0x831753dd7087cac61ab5644b308642cc1c33dc13", "QuickSwap", "quick.png",
        true, false, false, "QUICK", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x0f51bb10119727a7e5ea3538074fb341f56b09ad", "DAO Maker", "dao.png",
        true, false, false, "DAO", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xd55fce7cdab84d84f2ef3f99816d765a2a94a509", "Chain Games",
        "chain.png", true, false, false, "CHAIN", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0xC4C2614E694cF534D407Ee49F8E44D125E4681c4", "Chain Games",
        "chain.png", true, false, false, "CHAIN", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x80C62FE4487E1351b47Ba49809EBD60ED085bf52", "Clover Finance",
        "clv.png", true, false, false, "CLV", 18, true, "", "",
        mojom::kMainnetChainId, mojom::CoinType::ETH},
       {"0x765DE816845861e75A25fCA122bb6898B8B1282a", "Celo Dollar", "cusd.png",
        true, false, false, "CUSD", 18, true, "", "",
        mojom::kCeloMainnetChainId, mojom::CoinType::ETH},
       {"0x1a7e4e63778b4f12a199c062f3efdd288afcbce8", "agEUR", "ageur.png",
        true, false, false, "AGEUR", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xcc4304a31d09258b0029ea7fe63d032f52e44efe", "TrustSwap", "swap.png",
        true, false, false, "SWAP", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x8eef5a82e6aa222a60f009ac18c24ee12dbf4b41", "Tixl", "txl.png", true,
        false, false, "TXL", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xf94b5c5651c888d928439ab6514b93944eee6f48", "YIELD App", "yld.png",
        true, false, false, "YLD", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xeb986DA994E4a118d5956b02d8b7c3C7CE373674", "Gather", "gth.png", true,
        false, false, "GTH", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0x2b591e99afe9f32eaa6214f7b7629768c40eeb39", "HEX", "hex.png", true,
        false, false, "HEX", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xe0b52e49357fd4daf2c15e02058dce6bc0057db4", "agEUR", "ageur.png",
        true, false, false, "AGEUR", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0x4e78011ce80ee02d2c3e649fb657e45898257815", "Klima DAO", "klima.png",
        true, false, false, "KLIMA", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0xa2ca40dbe72028d3ac78b5250a8cb8c404e7fb8c", "Fear", "fear.png", true,
        false, false, "FEAR", 18, true, "", "", mojom::kPolygonMainnetChainId,
        mojom::CoinType::ETH},
       {"0x70c006878a5A50Ed185ac4C87d837633923De296", "Revv", "revv.png", true,
        false, false, "REVV", 18, true, "", "", mojom::kPolygonMainnetChainId,
        mojom::CoinType::ETH},
       {"0x7ceb23fd6bc0add59e62ac25578270cff1b9f619", "Weth", "weth.png", true,
        false, false, "WETH", 18, true, "", "", mojom::kPolygonMainnetChainId,
        mojom::CoinType::ETH},
       {"0xe6FC6C7CB6d2c31b359A49A33eF08aB87F4dE7CE", "IG Gold", "igg.png",
        true, false, false, "IGG", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"0xD74f5255D557944cf7Dd0E45FF521520002D5748", "Sperax USD", "usds.png",
        true, false, false, "USDS", 18, true, "", "",
        mojom::kArbitrumMainnetChainId, mojom::CoinType::ETH},
       {"0x5575552988A3A80504bBaeB1311674fCFd40aD4B", "Sperax", "spa.png", true,
        false, false, "SPA", 18, true, "", "", mojom::kArbitrumMainnetChainId,
        mojom::CoinType::ETH},
       {"0xA179248E50CE5AFb507FD8C54e08A66FBAC7B6Ff", "Freedom. Jobs. Business",
        "$fjb.png", true, false, false, "$FJB", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0xd6fDDe76B8C1C45B33790cc8751D5b88984c44ec", "StrikeX", "strx.png",
        true, false, false, "STRX", 18, true, "", "",
        mojom::kBinanceSmartChainMainnetChainId, mojom::CoinType::ETH},
       {"0xD8763CBa276a3738E6DE85b4b3bF5FDed6D6cA73", "Celo Euro", "ceur.png",
        true, false, false, "CEUR", 18, true, "", "",
        mojom::kCeloMainnetChainId, mojom::CoinType::ETH},
       {"0xba8a621b4a54e61c442f5ec623687e2a942225ef", "SandClock", "quartz.png",
        true, false, false, "QUARTZ", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xb26631c6dda06ad89b93c71400d25692de89c068", "Minds", "minds.png",
        true, false, false, "MINDS", 18, true, "", "", mojom::kMainnetChainId,
        mojom::CoinType::ETH},
       {"0xe8377a076adabb3f9838afb77bee96eac101ffb1", "MetaSoccer", "msu.png",
        true, false, false, "MSU", 18, true, "", "",
        mojom::kPolygonMainnetChainId, mojom::CoinType::ETH},
       {"CKaKtYvz6dKPyMvYq9Rh3UBrnNqYZAyd7iF4hJtjUvks", "Gari Network",
        "gari.png", true, false, false, "GARI", 9, true, "", "",
        mojom::kSolanaMainnet, mojom::CoinType::SOL}});

  return *tokens;
}

const std::vector<mojom::OnRampCurrency>& GetOnRampCurrenciesList() {
  static base::NoDestructor<std::vector<mojom::OnRampCurrency>> currencies({
      {"USD",
       "United States Dollar",
       {mojom::OnRampProvider::kWyre, mojom::OnRampProvider::kRamp}},
      {"EUR",
       "Euro",
       {mojom::OnRampProvider::kWyre, mojom::OnRampProvider::kRamp}},
      {"GBP",
       "British Pound Sterling",
       {mojom::OnRampProvider::kWyre, mojom::OnRampProvider::kRamp}},
  });

  return *currencies;
}

const std::string GetSardineNetworkName(const std::string& chain_id) {
  // key = chain_id, value = sardine_network_name
  static std::map<std::string, std::string> sardine_network_names = {
      {mojom::kMainnetChainId, "ethereum"},
      {mojom::kPolygonMainnetChainId, "ethereum"},
      {mojom::kAvalancheMainnetChainId, "avalanche"},
      {mojom::kFantomMainnetChainId, "fantom"},
      {mojom::kSolanaMainnet, "solana"}};
  auto sardine_network_pair = sardine_network_names.find(chain_id.c_str());

  if (sardine_network_pair == sardine_network_names.end()) {
    // not found
    return "";
  } else {
    return sardine_network_pair->second;
  }
}

const base::flat_map<std::string, std::string>& GetInfuraChainEndpoints() {
  static base::NoDestructor<base::flat_map<std::string, std::string>> endpoints(
      {{brave_wallet::mojom::kPolygonMainnetChainId,
        "https://mainnet-polygon.brave.com/"},
       {brave_wallet::mojom::kOptimismMainnetChainId,
        "https://mainnet-optimism.brave.com/"},
       {brave_wallet::mojom::kAuroraMainnetChainId,
        "https://mainnet-aurora.brave.com/"}});

  return *endpoints;
}

bool HasJupiterFeesForTokenMint(const std::string& mint) {
  static std::vector<std::string> mints(
      {"So11111111111111111111111111111111111111112",     // wSOL
       "EPjFWdd5AufqSSqeM2qN1xzybapC8G4wEGGkZwyTDt1v",    // USDC
       "Es9vMFrzaCERmJfrF4H2FYD4KCoNkY11McCe8BenwNYB",    // USDT
       "7vfCXTUXx5WJV5JADk17DUJ4ksgau7utNKj4b963voxs",    // WETH (Wormhole)
       "2FPyTwcZLUg1MDrwsyoP4D6s1tM7hAkHYRjkNb5w6Pxk",    // ETH (Sollet)
       "9n4nbM75f5Ui33ZbPYXn59EwSgE8CGsHtAeTH5YFeJ9E",    // BTC (Sollet)
       "qfnqNqs3nCAHjnyCgLRDbBtq4p2MtHZxw8YjSyYhPoL",     // wWBTC (Wormhole)
       "7dHbWXmci3dT8UFYWYZweBLXgycu7Y3iL6trKn1Y7ARj",    // stSOL
       "mSoLzYCxHdYgdzU16g5QSh3i5K3z3KZK7ytfqcJm7So",     // mSOL
       "FYpdBuyAHSbdaAyD1sKkxyLWbAP8uUW9h6uvdhK74ij1"});  // DAI

  return base::Contains(mints, mint);
}

}  // namespace brave_wallet
