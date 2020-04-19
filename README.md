Investment Manager
---------------

A web based application to manage investments. The application piggy-backs of the database used by gnuCash to provide additional functionality for investment management.
Specifically:
  - Taxation calculations (capital gains, interest and dividends. 
  - Multiple investment 'customers' 
  - Unit Trust/Mutual fund aproach to managing investments
  - Customer portfolio views

How to run
----------

The web application needs to run on a web server. The application needs to be built against fcgi libraries. See the Wt++ library for details.

Additional arguments: `-c wt_config.xml`

The configuration file specifies the configuration for using Google as
an authentication provider (you need to register with Google for this to
work), and customizes some email settings.

