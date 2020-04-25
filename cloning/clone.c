#include <stdio.h>
#include <string.h>

#include "clone.h"

/* Declaration of function to do replacement of REPLACE_ID_xx. Defined below. */
void do_replace(char *buffer, int update, int clone_id, char* line_out);

/* Declaration of function to read a list of agents. Defined below. */
void read_agent_list(char* agent_list);

/**
 * Function to clone households. Reads input file looking for households agents. When it finds one
 * it then looks for <id>xx</id> and makes a new id. Data is read from file called 0.xml and written
 * to 0_<clone_id>.xml.
 *
 * @param update	Value to be added to current id to make new agent. It must be sufficiently
 *					large to make the new id unique.
 * @clone_id		The number of this clone.
 */
int clone_households(int update, int clone_id) {

    /* Input and output files */
    FILE *f_in, *f_out;
    /* Buffer for line from input file */
    char buffer[1000000];
    /* Name tag for household agent - used to check when we're in a household */
    char *household_string = "<name>Household";
    /* Tag to check when we've reached the end of an agent */
    char *agent_end_string = "</xagent>";
    /* Tag to check for id data */
    char *id_string = "<id>";
    /* Used in checking substrings */
    char *pos = NULL;
    /* Flag set to 1 when we're reading household data */
    int in_household = 0;
    /* Id data read from buffer */
    int id;
    /* Name of output file */
    char outfile[100];

    /* Open 0.xml - File should already exist - could be symbolic link */
    f_in = fopen("0.xml", "r");
    /* Create name for output file based on clone_id and open it for writing */
    sprintf(outfile, "0_%d.xml", clone_id);
    f_out = fopen(outfile, "w");

    /* Print message if input file not found */
    if(f_in==NULL) {
        printf("0.xml file not found!\n");
    }
    else {
        /* Read input file line by line till end of file */
        while(!feof(f_in)) {
            fscanf(f_in, "%s", buffer);
            if (clone_id == 0) {
                /* The first clone is just a copy so just write out what we read */
                fprintf(f_out, "%s\n", buffer);
            }
            else {
                /* Check if we're reading household agent */
                pos = strstr(buffer, household_string);
                if (pos != NULL) {
                    /* Reading household so set flag and start an agent in output file */
                    in_household = 1;
                    /* We missed the opening <xagent> tag so write it now */
                    fprintf(f_out, "<xagent>");
                }
                if (in_household) {
                    /* Look for id tag on current line */
                    pos = strstr(buffer, id_string);
                    if (pos != NULL) {
                        /* Found id tag so get the id value */
                        sscanf(buffer, "<id>%d</id>", &id);
                        /* Make a new id */
                        id += update;
                        /* Write id tag to output file */
                        fprintf(f_out, "<id>%d</id>\n", id);
                    }
                    else {
                        /* No id tag here so write buffer to output file */
                        fprintf(f_out, "%s\n", buffer);
                    }
                    /* Check for the end of an agent as we don't want to clone non-agent data */
                    pos = strstr(buffer, agent_end_string);
                    if (pos != NULL) in_household = 0;
                }
            }
            /* Reset some variables for the next line from input file */
            buffer[0] = '\0';
            pos = NULL;
        }
    }

    /* Close files and return */
    if (f_in != NULL) fclose(f_in);
    fclose(f_out);
    return 1;

}

/**
 * Function to clone regions. Reads input file looking for agents to clone. When it finds one
 * it then looks for REPLACE_ID_xx and replaces this with a new id. Data is read from file called 
 * 0.xml and written to 0_<clone_id>.xml.
 *
 * @param update	Value to be added to current id to make new agent. It must be sufficiently
 *					large to make the new id unique.
 * @clone_id		The number of this clone.
 */
int clone_region(int update, int clone_id) {

    /* Input and output files */
    FILE *f_in, *f_out;
    /* Buffer for line from input file */
    char buffer[1000000];
    /* Tag to check when we've reached the end of an agent */
    char *agent_end_string = "</xagent>";
    /* Used in checking substrings */
    char *pos = NULL;
    /* Used in tokenising strings */
    char *pch = NULL;
    /* Line to be output to file when replacement has been done */
    char line_out[1100000];
    /* Flag set to 1 when we're reading data for an agent that needs to be cloned */
    int in_agent = 0;
    /* Name of output file */
    char outfile[100];
    /* List of agent types to clone and a back up copy to use since tokensing destroys the list */
    char name_list[1000], backup_name_list[1000];
    /* String used to check the <name> tag of an agent */
    char name_tag[100];

    /* Create the list of agent types to clone */
    read_agent_list(name_list);
    strcpy(backup_name_list, name_list);

    /* Open 0.xml - File should already exist - could be symbolic link */
    f_in = fopen("0.xml", "r");
    /* Create name for output file based on clone_id and open it for writing */
    sprintf(outfile, "0_%d.xml", clone_id);
    f_out = fopen(outfile, "w");

    /* Print message if input file not found */
    if(f_in==NULL) {
        printf("0.xml file not found!\n");
    }
    else {
        /* Read input file line by line till end of file */
        while(!feof(f_in)) {
            fscanf(f_in, "%s", buffer);
            if (clone_id == 0) {
                /* The first clone is just a copy but we have to do the replacement */
                do_replace(buffer, update, clone_id, line_out);
                /* Write the line to the output file */
                fprintf(f_out, "%s\n", line_out);
            }
            else {
                /* Reinstate name_list since tokenising destroys it */
                strcpy(name_list, backup_name_list);
                /* Go through the list of agent types to be cloned and check whether we have one */
                pch = strtok(name_list, ",");
                while (pch != NULL) {
                    /* Create the <name> tag */
                    sprintf(name_tag, "<name>%s</name>", pch);
                    /* Look for name tag on this line */
                    pos = strstr(buffer, name_tag);
                    if (pos != NULL) {
                        /* Found it! Set flag so we know we need to clone */
                        in_agent = 1;
                        /* We missed the opening <xagent> tag so write it now */
                        fprintf(f_out, "<xagent>\n");
                        /* Don't look for any more agent types from list */
                        break;
                    }
                    /* Go on to next type in list */
                    pch = strtok(NULL, ",");
                }
                if (in_agent) {
                    /* We're in an agent that needs cloning so do the replacement */
                    do_replace(buffer, update, clone_id, line_out);
                    /* Write line to output file */
                    fprintf(f_out, "%s\n", line_out);
                    /* Check for the end of an agent as we don't want to clone non-agent data */
                    pos = strstr(buffer, agent_end_string);
                    if (pos != NULL) in_agent = 0;
                    /* Reset some variables for the next line from input file */
                    buffer[0] = '\0';
                }
            }
        }
    }

    /* Close files and return */
    if (f_in != NULL) fclose(f_in);
    fclose(f_out);
    return 1;

}

/**
 * Function to read a list of agents from the file "agent_list.txt".
 * @param agent_list	Character array to be filled with agent names. Names will be comma separated.
 */
void read_agent_list(char *agent_list) {

    /* Input file */
    FILE *f_in;
    /* Buffer for line from input file */
    char buffer[1000000];
    /* Count of number of lines in file */
    int line_count = 0;

    /* Initialise agent_list */
    agent_list[0] = '\0';

    /* Open agent_list.txt - File should already exist */
    f_in = fopen("agent_list.txt", "r");

    /* Print message if input file not found */
    if(f_in==NULL) {
        printf("agent_list.txt file not found!\n");
    }
    else {
        /* Read input file line by line till end of file */
        while(!feof(f_in)) {
            fscanf(f_in, "%s", buffer);
            if (buffer[0] != '\0') {
                /* If we read more than one line add a comma to agent list */
                if (line_count > 0) strcat(agent_list, ",");
                strcat(agent_list, buffer);
                line_count++;
            }
            buffer[0] = '\0';
        }
    }

    /* Close input file */
    if (f_in != NULL) fclose(f_in);
 
}

/**
 * Function to replace REPLACE_ID_xx with the id for the cloned object. The new id is xx+update.
 *
 * @param buffer	Line read from the input file
 * @param update	Value to be added to current id to make new agent. It must be sufficiently
 *					large to make the new id unique.
 * @param clone_id  Id of this clone.
 * @param line_out	On output the line with replacement done. Must be dimensioned by calling function
 *					and be large enough to hold the text.
 */
void do_replace(char *buffer, int update, int clone_id, char* line_out) {

    /* Text the indicates an id to be replaced */
    char *replace_marker = "REPLACE_ID_";
    /* Used in checking substrings */
    char *pos = NULL;
    /* Used in tokenising strings */
    char *pch = NULL;
    /* A work array */
    char work[1000];
    /* Strings for the opening and closing xml tags on a line and the data contained therein */
    char tag_start[50], tag_end[50], data[1000000];
    /* String representation of new id */
    char id_string[8];
    /* Id as integer, length of xml tag, number of tokens read on a line, depth of '{' brackets
     * used in array or ADT */
    int id, len_tag, token_count, bracket_depth;

    /* Check whether there is any replacement to do */
    pos = strstr(buffer, replace_marker);
    if (pos != NULL) {
        /* Initialised token count */
        token_count = 0;
        /* Look for > that ends the opening xml tag */
        pos = strstr(buffer, ">");
        /* Work out the length of the tag */
        len_tag = pos > buffer ? pos-buffer : buffer-pos;
        /* Create the opening tag */
        strncpy(tag_start, buffer, len_tag+1);
        tag_start[len_tag+1] = '\0';
        /* Start the output line with this tag */
        strncpy(line_out, buffer, len_tag+1);
        line_out[len_tag+1] = '\0';
        /* Look for </ that starts the closing xml tag */
        pos = strstr(buffer, "</");
        /* Create the closing tag */
        strcpy(tag_end, pos);
        tag_end[len_tag+2] = '\0';
        /* Look for the end of the opening tag so we can get the tag's data */
        pos = strstr(buffer, ">");
        /* Copy the data from the tag */
        strncpy(data, pos+1, strlen(buffer)-strlen(tag_start)-strlen(tag_end));
        data[strlen(buffer)-strlen(tag_start)-strlen(tag_end)] = '\0';
        /* We will tokenise the data if it's a list or an ADT (or both!) */
        pch = strtok(data, ",");
        while (pch != NULL) {
            /* Look for replaceable id in this token */
            pos = strstr(pch, replace_marker);
            /* We're starting a new token so if it's not the first we need a comma separator */
            if (token_count > 0) strcat(line_out, ",");
            if (pos != NULL) {
                /* Initially copy the token to work so it can be worked on during replacement.
                 * This may be overwritten later if the token contains { or } */
                strcpy(work, pch);
                /* We're looking for opening { in the token */
                pos = strstr(pch, "{");
                if (pos != NULL) {
                    /* Initialise count of brackets */
                    bracket_depth = 0;
                    /* Count brackets and add them to the output line */
                    while (pch[bracket_depth] == '{') {
                        strcat(line_out, "{");
                        bracket_depth++;
                    }
                    /* Copy the token without brackets to work */
                    strncpy(work, pch+bracket_depth, strlen(pch)-bracket_depth);
                    work[strlen(pch)-bracket_depth] = '\0';
                }
                /* Now we're looking for closing brackets in the token */
                bracket_depth = 0;
                pos = strstr(pch, "}");
                if (pos != NULL) {
                    /* Count closing brackets. Can't add them to output line because we haven't
                     * done the data yet! */
                    while (pch[strlen(pch)-1-bracket_depth] == '}') bracket_depth++;
                    /* Copy the token without brackets to work */
                    strncpy(work, pch, strlen(pch)-bracket_depth-1);
                    work[strlen(pch)-bracket_depth] = '\0';
                }
                /* The token will now have the correct format so get the id value */
                sscanf(work, "REPLACE_ID_%d", &id);
                /* Make a new id */
                id += update;
                /* Convert the numeric id into a string */
                sprintf(id_string, "%d", id);
                /* Add the id string to the output line */
                strcat(line_out, id_string);
                /* Add any closing brackets */
                for (; bracket_depth > 0; bracket_depth--) {
                    strcat(line_out, "}");
                }
            }
            else {
                /* No replace markers in this toke so add it to the output line */
                strcat(line_out, pch); 
            }
            /* Move on to the next token */
            pch = strtok(NULL, ",");
            token_count++;
        }
        /* All tokens done so add the end tag */
        strcat(line_out, tag_end);
    }
    else {
        /* No replacement necessary so we just need to check for <region_id> or <partition_id> */
        pos = strstr(buffer, "<region_id>");
        if (pos != NULL) {
            /* region_id found */
            sscanf(buffer, "<region_id>%d</region_id>", &id);
            id += clone_id;
            sprintf(line_out, "<region_id>%d</region_id>", id);
        }
        else {
            pos = strstr(buffer, "<partition_id>");
            if (pos != NULL) {
                /* partition_id found */
                sscanf(buffer, "<partition_id>%d</partition_id>", &id);
                if (id > 0) id += clone_id;
                sprintf(line_out, "<partition_id>%d</partition_id>", id);
            }
            else {
                /* Neither found so just copy the given line to the output line. */
                strcpy(line_out, buffer);
            }
        }
    }

}


