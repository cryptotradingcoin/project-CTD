Masternode config
=======================

## Single masternode on Linux VPS + cold control wallet on local PC
------
This guide is for a single masternode, on a Ubuntu 16.04 64bit server(1GB RAM) and will be controlled from the wallet on your local computer.

First the basic requirements:
* 1000 CTD (https://crex24.com/exchange/CTD-BTC)
* A main computer(Your everyday computer)
* Masternode Server(The computer that will be on 24/7)
* A unique IP address for EACH masternode

The basic reasoning for these requirements is that, you get to keep your CTD in your local wallet, and host your masternode remotely, securely.

For this guide, I’m going to refer to your main computer’s wallet as the main wallet, and the masternode wallet as the masternode wallet.

-------

### I. Deploy VPS and configuration

1. Get a VPS server with min. 1GB RAM and Ubuntu 16.04 as operating system
2. Get PUTTY for your operating system from https://www.putty.org
    * Always use mouse selection for COPY text from PUTTY to WINDOWS
    * Always use right button click for PASTE text in PUTTY from WINDOWS
3. RUN script bellow(select from below, COPY, PASTE in Putty and press ENTER):

```wget https://github.com/cryptotradingcoin/project-CTD/releases/download/v0.11/CTD_v0.11_setup_tar.sh```
```bash CTD_v0.11_setup_tar.sh```
    
   (It may take 2-3 minutes. It will automatically install and configure masternode wallet for your masternode server!)
4. **Note VPS_IP:PORT and Masternode Privatekey**(this will be the masternode’s privkey) in Notepad(text file)! - We’ll use this later…

--------

### II. Install main wallet and configuration

1. Go to https://www.cryptotradingcoin.net/ and download wallet for your windows
2. Unpack it and launch ***ctdcoin-qt.exe***
3. Select "Use a custom data directory" and use C:\CTD\data as folder
4. TOOLS -> DEBUG CONSOLE and type the following command:
   ```getaccountaddress ctdmn1```
5. Send 1000 CTD to this address.(Make sure this is 100% only 1000; No less, no more.) and wait for 30 confirmations
6. Still in the main wallet, enter the command into the console:
   ```masternode outputs``` (This gets the proof of transaction of sending 1000)
7. Still on the main computer, go into the SafeInsure data directory(C:\CTD\data)
   Find masternode.conf and add the following line to it:   
   
   ```<Name of Masternode(Use the name you entered earlier for simplicity)> <VPS_IP:PORT- The result of Step I.4> <Masternode Privatekey- The result of Step I.4> <Result of Step II.7> <The number after the long line in Step II.7>```
   
   ***Substitute it with your own values and without the “<>”s***
   
   Example:
   
   ```ctdmn1 133.133.133.133:33263 235dBB6LAhF6Uum2CPGcFLJXWSPCXa9aqLVpTZmWLDHT1eL6M1v f929399390594fc2a0b2935bece819480db0749b59e0d65ffb54c9bfeaed3d10 0```
      
9. Save it, close and restart the main wallet. **Wait for full sync**.
10. Masternodes tab -> Start all
   
#### *Congratulations! You have successfully created your masternode!*






The masternode config allows you to control masternodes from a single wallet. The wallet needs to have a valid collateral output of 1000 coins for each masternode. To use this, place a file named masternode.conf in the data directory of your install:
 * Windows: %APPDATA%\CTD\ or C:\CTD\data 
 * Mac OS: ~/Library/Application Support/CTD/
 * Unix/Linux: ~/.ctdcoin/

The new masternode.conf format consists of a space seperated text file. Each line consisting of an alias, IP address followed by port, masternode private key, collateral output transaction id, collateral output index, donation address and donation percentage

Example:
```
ctdmn1 127.0.0.2:33263 235dBB6LAhF6Uum2CPGcFLJXWSPCXa9aqLVpTZmWLDHT1eL6M1v f929399390594fc2a0b2935bece819480db0749b59e0d65ffb54c9bfeaed3d10 0
```

In the example above:
* the collateral for mn1 consists of transaction 2bcd3c84c84f87eaa86e4e56834c92927a07f9e18718810b92e0d0324456a67c, output index 0 has amount 1000

The following new RPC commands are supported:
* list-conf: shows the parsed masternode.conf
* masternode start-alias \<alias\>
* masternode stop-alias \<alias\>
* masternode start-many
* masternode stop-many
* masternode outputs: list available collateral output transaction ids and corresponding collateral output indexes

When using the multi masternode setup, it is advised to run the wallet with 'masternode=0' as it is not needed anymore.
