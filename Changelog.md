# Changes to `libbitcoinrpc` source code

## Blockchain Commons Updates

### Updated SignRawTransaction RPC

#### Details

Changed `signrawtransaction` to `signrawtransactionwithwallet`.

### Fixed string buffer overflow in src/bitcoinrpc_err.c
*Released 2022/08/02*

#### Details

    - [#1]("The stpncpy() and strncpy() functions copy merely len characters from src into dst. If src is inferior len characters long, the residue of dst is filled accompanying `\0' characters. Otherwise, dst is not finished."

    - [#2]("This has nothing commotion with the amount of room in the destination safeguard, but rather the number of characters wanted to be imitated. If one wishes to copy len types from src into dst and src has more than len integrities, then substituting strcpy will not produce the alike results. Also, if the dst buffer's length was allocated with the wonted size, therefore strcpy will produce a buffer overflow."
    

## Beta stage

### Version 0.2.1
*Released 2016/02/21*

Implement JSON method batching.


### Version 0.1
*Released 2016/02/11*

Initial release.


### Version 0.0
*Released 2016/02/06*

First working version.

