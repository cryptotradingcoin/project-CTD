// Copyright (c) 2012-2014 The Bitcoin developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2019-2019 The Ctdcoin developers
//
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

/**
 * network protocol versioning
 */

static const int PROTOCOL_VERSION = 33201;

//! initial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 301;

//! In this version, 'getheaders' was introduced.
static const int GETHEADERS_VERSION = 33210;

//! disconnect from peers older than this proto version
static const int MIN_PEER_PROTO_VERSION_ENFORCEMENT = 33201;

//! nTime field added to CAddress, starting with this version;
//! if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 33221;

//! only request blocks from nodes outside this range of versions
static const int NOBLKS_VERSION_START = 33250;
static const int NOBLKS_VERSION_END = 33281;

//! BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 33601;

//! "mempool" command, enhanced "getdata" behavior starts with this version
static const int MEMPOOL_GD_VERSION = 33604;

//! "filter*" commands are disabled without NODE_BLOOM after and including this version
static const int NO_BLOOM_VERSION = 33611;


#endif // BITCOIN_VERSION_H
