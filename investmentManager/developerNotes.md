Investment Manager
==================

Language
--------
The application is written in C++. The compiler used is g++ from gcc. Any version of the C++ language can be used including C++20 
and later versions. It is suggested that all code added be written using the later version and language paradigms.

Libraries
---------
Use is made of the following C++ libraries.

> Boost Library
> General Class Library (GCL)
> Math Class Library (MCL)
> Storage Class Library (SCL)

gnuCash Tables
--------------
The existing structure of the gnuCash tables is maintained. If additional information is required to be stored for gnuCash tables,
then additional tables with linkage back to the gnuCash tables is used. While it is theoretically possible to use the 'slots' table
to store additional information, this may confuse gnuCash as the 'slots' table is already used. Additional informatation may create
errors now or later with gnuCash.

### 'commodities'
The commodities table is used for storage of the commodities (shares, currencies) that are used in the program. Entries can be added 
and removed in the gnuCash application. 

### 'prices'
The prices table is used to store commodity (shares, currencies) values over time.

#### Version2
With the version 2 table, the prices are stored as a numerator/denominator pair.

If a large number of commodities are being tracked this table could grow fairly large. For this reason, it is recommended that to 
improve performance, two indexes be added to this table:
1. commodity_guid: As there are a number of queries that search for specific commodities this index is recommended.
2. date: The date column will benefit from an index as there are a number of queries in investmentManager that will use the date 
column to optimise searches and order by.

