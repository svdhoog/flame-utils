Cloning regions
Author: Sander van der Hoog, Uni Bielefeld

Commands:

0. Executable clone_serial: 'make serial' to compile in serial.

1. From PopGUI folder output a 0.xml with replacement markers:
python $POP_GUI_DIR/instantiate.py -r $SIM_DIR/0.pop $SIM_DIR/0_markers.xml

2. Cloning script replaces markers with new IDs:
./clone.sh 0_markers.xml 1 0_cloned_2R.xml -j


Tags that are replaced:
 <id>: <REPLACE_ID_id>
 <gov_id>: <REPLACE_ID_gov_id> to ensure new households are linked to the government in the region
 <bank_id>: <REPLACE_ID_bank_id> to ensure new households are linked to the bank(s) in the region

NOTE: If you do not want the <gov_id> to be updated do a search-replace in the 0_markers.xml file:
 <gov_id>REPLACE_ID_  with  <gov_id>


Main idea: replicating a region to multiple regions, with similar composition of agent population

- The composition of the unit population remains constant, and is multiplied across regions.
- The interdependencies between firms-banks, households-banks, firms-govs and households-govs should remain in tact.
- The pop-instantiate output with replacement markers puts replacement markers on all IDs, gov_ids and bank_id in the memory of the agents.
- The choice which agent types to clone is made in the cloning code, using the file agent_list.txt
- For those agent types that are not listed in this file, they will not be cloned, and the string "REPLACE_ID_" will just be removed. This means the IDs from agents in region 1 will be used.

agent_list.txt
==============
Suggested setting:

Firm
Household
Government
Mall
Bank 

NOTE: Do not include Government, Mall, Bank, then you remain with "<gov_id>REPLACE_ID_" in the cloned 0.xml file.


Example:
========
In Firm, there is a dependency on the mall_id:
<malls_sales_statistics>{{REPLACE_ID_7,...

After cloning, this will be replaced by the new Mall id (if Malls are not present in the cloning list it will be simply 7).


Example:
Start with a small Eurace 0.xml file with 1 agent per agent type (but 2 banks).
This means 10 agents. Contents of the file agent_list.txt: Firm Household

After cloning:
Initial 0.xml contains 10 agents
Clone iteration 0
Clone id = 0
Update value = 0
Clone iteration 1
Clone id = 1
Update value = 10
Add cloned data 1
New 0.xml contains 12 agents

The output contains 12 agents: 10+2 cloned

Firm 1:
<id>REPLACE_ID_1</id>
<region_id>1</region_id>
<gov_id>REPLACE_ID_5</gov_id>
<bank_id>REPLACE_ID_10</bank_id>

Firm 10+1:
<id>11</id>
<region_id>2</region_id>
<gov_id>15</gov_id> =5+10
<bank_id>20</bank_id> =10+10

Household 6:
<id>REPLACE_ID_6</id>
<region_id>1</region_id>
<gov_id>REPLACE_ID_5</gov_id>
<bank_id>REPLACE_ID_9</bank_id>

Household 16: = 6+10
<id>16</id>
<region_id>2</region_id>
<gov_id>15</gov_id> = 5+10
<bank_id>19</bank_id> =9+10



Cloning ONLY households - blowing up the size of a single region
=======================
From the README.txt:
"The code is pretty well commented if you need to change it. If you want
to use the old household cloning (cloning household agents only), edit clone_serial.c and clone_parallel.c to
uncomment the clone_households line and comment out the clone_region line."

NOTE: This does not work properly anymore with the instantiate output from popgui.
Use a normal 0.xml file as input for this cloning method.

0. Edit clone_serial.c
1. Executable clone_serial: 'make serial' to compile in serial.
2. Using original 0.xml file, cloning script replaces IDs with new IDs only for households:
./clone.sh 0.xml 1 0_cloned_2R.xml -j

Example:

Original household:
<id>6</id>
<region_id>1</region_id>
<neighboring_region_ids>{}</neighboring_region_ids>
<gov_id>5</gov_id>
<day_of_month_to_act>4</day_of_month_to_act>
<payment_account>15.0</payment_account>
<bank_id>10</bank_id>

New household:
<id>16</id>
<region_id>1</region_id>
<neighboring_region_ids>{}</neighboring_region_ids>
<gov_id>5</gov_id>
<day_of_month_to_act>4</day_of_month_to_act>
<payment_account>15.0</payment_account>
<bank_id>10</bank_id>


PROBLEM: The problem with this method is that the banks do not account for the increased payment accounts of the newly cloned households.
Only use this method if this is not a problem (if you correct this during the simulation).
