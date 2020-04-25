README for Simulation Validation Rules

Date: 9.5.2017
Author: Sander van der Hoog

REQUIREMENTS
- XMML of model
- Rules file
- Database output in SQL

SETTINGS
All settings are set in the script:
 # run.sh
 
DB_DIR: Folder with a single iters.db file.


OUTPUTS
- In plain text format: output.txt
- In pretty formatted HTML: out.html


Results folder
==============
Folders:
- no_data_input: empty mortgages
- data_input: with sampled  mortgages

Default setting in pop file is to set the firm day_of_month_to_act=rand(0,19). This causes some validation rules to be invalid, due to shifting of the balance sheets.
Solution: set firm.day_of_month_to_act=1 for all firms.

v1: Firm day_of_month_to_act=random; causes some rules to be violated
v2: Firm day_of_month_to_act=1; no HH stored, causes rules with HH data to be violated
v3: Firm day_of_month_to_act=1; HH stored; should resolve all rules. [10.10.2016]
v4: Firm day_of_month_to_act=1; HH stored; should resolve all rules. [9.5.17]

Status 10.10.2016:
Rules with problems
3
16
28
32
33

Status 9.5.2017:
Rules with problems
