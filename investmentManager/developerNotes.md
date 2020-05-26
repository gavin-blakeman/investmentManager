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

### UUIDs
gnuCash uses UUIDs to uniquely identify records in the database (primary keys), rather than using integer primary keys. These are
represented as VARCHAR(32) in the database. (Note this could be simplified to CHAR(32) and they are fixed length strings.) When
UUIDs are needed to be generated, the boost::uuid library is used. However, all UUIDs are kept as strings in the queries and other
logic. While there could be advantages to comparing binary integers rather than std::strings, the queries are all based on string
values and if binary integer representations are used, there is continual conversion between strings and binary integers. This is
considered to be sub-optimal. If gnuCash were to ever change the table formats, this could be changed.
