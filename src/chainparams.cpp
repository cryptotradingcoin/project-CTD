// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2019-2019 The Ctdcoin developers
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "base58.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>


using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    return genesis;
}


static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Cryptotrading system 2019";
	const CScript genesisOutputScript = CScript() << ParseHex("04c950d2a03eedc8661856af19d3db23e6b739cdddd0ae773ce6bcdb5d0eb1a27c708f3f878824b097729c56d1e398112142053cb89660bea64e382df66aee763d") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{

    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}


static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
		(0, uint256("0x00000cdb3f6db4266d4dac5026718db858a7923050cdddfd35c9416a6759eaed"))
		;
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1556615607, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000cdb3f6db4266d4dac5026718db858a7923050cdddfd35c9416a6759eaed"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1556615607,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00000cdb3f6db4266d4dac5026718db858a7923050cdddfd35c9416a6759eaed"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1556615607,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x41;
        pchMessageStart[2] = 0x52;
        pchMessageStart[3] = 0x46;
        vAlertPubKey = ParseHex("0479b1d427b49cfd0c118dad2fc03ef411372c6a1aaf4f47608762b265fc5b6a3ae589e8d86570baaabb460cbc647a660fc7d069b1f4ab619d2d15552a5a63b3a0");
        nDefaultPort = 33263;
        bnProofOfWorkLimit = ~uint256(0) >> 20; //SafeInsure starting difficulty is 1 / 2^12
		
        nSubsidyHalvingInterval = 900001;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; //SafeInsure: every block
        nTargetSpacing = 1 * 60; //SafeInsure: 1 minute
        nLastPOWBlock = 310;
        nMaturity = 150;
        nMasternodeCountDrift = 20;
	nMasternodeColleteralLimxDev = 1000;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 10000000 * COIN;
		
        genesis = CreateGenesisBlock(1556615607, 465887, 0x1e0ffff0, 1, 0 * COIN);
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000cdb3f6db4266d4dac5026718db858a7923050cdddfd35c9416a6759eaed"));
        assert(genesis.hashMerkleRoot == uint256("0x16e804c67dae111a7f813c64bdc965997068ea6a98b978a56206cfa8c37284a7"));
		
		vSeeds.push_back(CDNSSeedData("ctd1", "ctd1.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd2", "ctd2.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd3", "ctd3.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd4", "ctd4.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd5", "ctd5.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd6", "ctd6.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd7", "ctd7.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd8", "ctd8.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd9", "ctd9.cryptotradingcoin.net"));
		vSeeds.push_back(CDNSSeedData("ctd10", "ctd10.cryptotradingcoin.net"));

		
		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28); //Safeinsure addresses start with 'C'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 65); //Safeinsure script addresses start with 'T'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 30); //Safeinsure private keys start with 'D'

	//SafeInsure BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();

	//SafeInsure BIP32 pubkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

	//BIP44 coin type is '0X80000a00' from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0404a0de566f289881918144ad982fd562c601197a314e90657f561414f9fee2893ab4568d76a180e7f877bfb96074ec4fdd87456e2b280fc0aec35bd7109c49aa";
		nStartMasternodePayments = 1556615607;

		CBitcoinAddress address;
		std::string strAddress = "CSWRSSZeUdmJ6EQNPFiRCvagG9Jr1bZZZk";
		SelectParams(CBaseChainParams::MAIN);
		assert(address.SetString(strAddress));
		masternodeTestDummyAddress = GetScriptForDestination(address.Get());
	}

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
       
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
       
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 33333;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
