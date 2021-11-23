# EMA C++ UserAuthn Authentication Example
This EMA C++ example demonstrates how to get tokens from a token generate and use retrieved tokens to login to ADS. For more information, please refer to this article. 

The example uses the **curl** library to get tokens and uses **cJSON** to parse response messages. 

The example requires the following parameters.
```
Options:
  -?                            Shows this usage

  -authurl <authurl>            Required: Authentication URL to get a token (e.g. http://<AuthServer>:8443/getToken)
  -username <username>          Required: Username
  -password <password>          Required: Password
  -service <service name>       Required: Service name
  -item <ric>                   Optional: A RIC
```
For example:

```
CPPAuthExample -authurl "http://localhost:8443/getToken" -username authuser1 -password password -service ELEKTRON_DD -item PTT.BK
```
The output is:

```
Following options are selected:
appId = 256
authurl = http://localhost:8443/getToken
username = authuser1
password = *****
service = ELEKTRON_DD
item = PTT.BK
{"success":true,"message":"Enjoy your token!","token":"20QsEiJAi0yZfI6n9LsYkOge2k"}
True
20QsEiJAi0yZfI6n9LsYkOge2k
loggerMsg
    TimeStamp: 15:26:16.601
    ClientName: ChannelCallbackClient
    Severity: Success
    Text:    Received ChannelUp event on channel Channel_1
        Instance Name Consumer_1_1
        Connected component version: ads3.5.3.L1.linux.rrg 64-bit
loggerMsgEnd


Received login refresh message

RefreshMsg
    streamId="1"
    domain="Login Domain"
    Solicited
    RefreshComplete
    ClearCache
    state="Open / Ok / None / 'Login accepted by host replablinux5.'"
    itemGroup="00 00"
    name="wasin"
    nameType="1"
    Attrib dataType="ElementList"
        ElementList
            ElementEntry name="ApplicationId" dataType="Ascii" value="256"
            ElementEntry name="ApplicationName" dataType="Ascii" value="ADS"
            ElementEntry name="Position" dataType="Ascii" value="192.168.0.184/net"
            ElementEntry name="ProvidePermissionProfile" dataType="UInt" value="0"
            ElementEntry name="ProvidePermissionExpressions" dataType="UInt" value="1"
            ElementEntry name="SingleOpen" dataType="UInt" value="1"
            ElementEntry name="AllowSuspectData" dataType="UInt" value="1"
            ElementEntry name="SupportOMMPost" dataType="UInt" value="1"
            ElementEntry name="SupportBatchRequests" dataType="UInt" value="1"
            ElementEntry name="SupportEnhancedSymbolList" dataType="UInt" value="1"
            ElementEntry name="SupportViewRequests" dataType="UInt" value="1"
            ElementEntry name="SupportStandby" dataType="UInt" value="0"
            ElementEntry name="SupportOptimizedPauseResume" dataType="UInt" value="0"
            ElementEntry name="AuthenticationTTReissue" dataType="UInt" value="1637660744"
            ElementEntry name="AuthenticationErrorCode" dataType="UInt" value="0"
            ElementEntry name="AuthenticationErrorText" dataType="Ascii" value="Success"
        ElementListEnd

    AttribEnd
RefreshMsgEnd


Received refresh

RefreshMsg
    streamId="5"
    domain="MarketPrice Domain"
    Solicited
    RefreshComplete
    ClearCache
    state="Open / Ok / None / 'All is well'"
    itemGroup="00 02"
    permissionData="03 11 A7 67 61 C0"
    qos="RealTime/TickByTick"
    seqNum="45008"
    name="PTT.BK"
    nameType="1"
    serviceId="4519"
    serviceName="ELEKTRON_DD"
    Payload dataType="FieldList"
        FieldList FieldListNum="2" DictionaryId="1"
            FieldEntry fid="1" name="PROD_PERM" dataType="UInt" value="6761"
            FieldEntry fid="2" name="RDNDISPLAY" dataType="UInt" value="142"
            FieldEntry fid="3" name="DSPLY_NAME" dataType="Rmtes" value="PTT"
            FieldEntry fid="4" name="RDN_EXCHID" dataType="Enum" value="158"
            FieldEntry fid="5" name="TIMACT" dataType="Time" value="08:26:21:000:000:000"
            FieldEntry fid="6" name="TRDPRC_1" dataType="Real" value="37.25"
            FieldEntry fid="7" name="TRDPRC_2" dataType="Real" value="37.25"
            FieldEntry fid="8" name="TRDPRC_3" dataType="Real" value="37.25"
            FieldEntry fid="9" name="TRDPRC_4" dataType="Real" value="37.25"
            FieldEntry fid="10" name="TRDPRC_5" dataType="Real" value="37.25"
            FieldEntry fid="11" name="NETCHNG_1" dataType="Real" value="0.00"
            FieldEntry fid="12" name="HIGH_1" dataType="Real" value="37.75"
            FieldEntry fid="13" name="LOW_1" dataType="Real" value="37.00"
            FieldEntry fid="14" name="PRCTCK_1" dataType="Enum" value="1"
            FieldEntry fid="15" name="CURRENCY" dataType="Enum" value="764"
            FieldEntry fid="16" name="TRADE_DATE" dataType="Date" value="23 NOV 2021"
```



