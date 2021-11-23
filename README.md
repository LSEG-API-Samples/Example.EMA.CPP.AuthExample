# Example.EMA.CPP.AuthExample
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



