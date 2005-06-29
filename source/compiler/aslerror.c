
/******************************************************************************
 *
 * Module Name: aslerror - Error handling and statistics
 *              $Revision: 1.31 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government.  In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/


#include "AslCompiler.h"


char                        *AslMessages [] = {
    NULL,
    "Memory allocation failure",
    "Could not open input file",
    "Could not create output filename",
    "Could not open output AML file",
    "Could not create listing filename",
    "Could not open listing file",
    "Could not create debug filename",
    "Could not open debug file",
    "Could not open include file",
    "Package length too long to encode",
    "Invalid priority value",
    "Invalid performace/robustness value",
    "Method variable not initialized:",
    "Method argument is invalid:",
    "Unsupported feature:",
    "Use of reserved word:",
    "Effective AML buffer length is zero",
    "Effective AML package length is zero",
    "Mixed return types in method",
    "Cannot find/access object",
    "Nested comment found",
    "Reserved method has too many arguments:",
    "Reserved method has too few arguments:",
    "Reserved method must return a value:",
    "Too many arguments:",
    "Too few arguments:",
    "Called method returns no value:",
    "Called method may not always return a value:",
    "Internal compiler error:",
    "Invalid backwards offset",
    "Unknown reserved name:",
    "Name already exists in scope:",
    "Invalid type:",
};


char                        *AslErrorLevel [] = {
    "Error  ",
    "Warning",
};


/*******************************************************************************
 *
 * FUNCTION:    AeAddToErrorLog
 *
 * PARAMETERS:  Enode       - An error node to add to the log
 *
 * RETURN:      None
 *
 * DESCRIPTION: Add a new error node to the error log.  The error log is
 *              ordered by the "logical" line number (cumulative line number
 *              including all include files.)
 *
 ******************************************************************************/

void
AeAddToErrorLog (
    ASL_ERROR_MSG           *Enode)
{
    ASL_ERROR_MSG           *Next;
    ASL_ERROR_MSG           *Prev;


    if (!Gbl_ErrorLog)
    {
        Gbl_ErrorLog = Enode;
        return;
    }


    /* List is sorted according to line number */

    if (!Gbl_ErrorLog)
    {
        Gbl_ErrorLog = Enode;
        return;
    }

    /* Walk error list until we find a line number greater than ours */

    Prev = NULL;
    Next = Gbl_ErrorLog;

    while ((Next) &&
           (Next->LogicalLineNumber <= Enode->LogicalLineNumber))
    {
        Prev = Next;
        Next = Next->Next;
    }

    /* Found our place in the list */

    Enode->Next = Next;

    if (Prev)
    {
        Prev->Next = Enode;
    }
    else
    {
        Gbl_ErrorLog = Enode;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AePrintException
 *
 * PARAMETERS:  Where       - Where to send the message
 *              Enode       - Error node to print
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print the contents of an error node.
 *
 ******************************************************************************/

void
AePrintException (
    FILE                    *Where,
    ASL_ERROR_MSG           *Enode)
{


    /* Pring filename and line number if present and valid */

    if (Enode->Filename)
    {

        fprintf (Where, "%12s ", Enode->Filename);

        if (Enode->LineNumber)
        {
            fprintf (Where, "%5d: ", Enode->LineNumber);
        }
    }

    /* NULL message ID, just print the raw message */

    if (Enode->MessageId == 0)
    {
        fprintf (Where, "%s\n",
                    Enode->Message);
    }

    /* Decode the message ID */

    else
    {
        fprintf (Where, "%s %04.4d - %s %s\n",
                    AslErrorLevel[Enode->Level],
                    Enode->MessageId + ((Enode->Level+1) * 1000),
                    AslMessages[Enode->MessageId],
                    Enode->Message);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AePrintErrorLog
 *
 * PARAMETERS:  Where           - Where to print the error log
 *
 * RETURN:      None
 *
 * DESCRIPTION: Print the entire contents of the error log
 *
 ******************************************************************************/

void
AePrintErrorLog (
    FILE                    *Where)
{
    ASL_ERROR_MSG           *Enode = Gbl_ErrorLog;


    while (Enode)
    {
        AePrintException (Where, Enode);
        Enode = Enode->Next;
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AslCommonError
 *
 * PARAMETERS:  Level               - Seriousness (Warning/error, etc.)
 *              MessageId           - Index into global message buffer
 *              CurrentLineNumber   - Actual file line number
 *              LogicalLineNumber   - Cumulative line number
 *              Filename            - source filename
 *              ExtraMessage        - additional error message
 *
 * RETURN:      New error node for this error
 *
 * DESCRIPTION: Create a new error node and add it to the error log
 *
 ******************************************************************************/

ASL_ERROR_MSG *
AslCommonError (
    UINT8                   Level,
    UINT8                   MessageId,
    UINT32                  CurrentLineNumber,
    UINT32                  LogicalLineNumber,
    char                    *Filename,
    char                    *ExtraMessage)
{
    char                    *LocalMessage = "";
    UINT32                  MessageSize;
    char                    *MessageBuffer;
    ASL_ERROR_MSG           *Enode;


    if (ExtraMessage)
    {
        LocalMessage = ExtraMessage;
    }

    MessageSize     = strlen (LocalMessage) + 1;
    MessageBuffer   = UtLocalCalloc (MessageSize);
    Enode           = UtLocalCalloc (sizeof (ASL_ERROR_MSG));

    STRCPY (MessageBuffer, LocalMessage);
    Enode->Filename             = Filename;
    Enode->MessageId            = MessageId;
    Enode->Level                = Level;
    Enode->LineNumber           = CurrentLineNumber;
    Enode->LogicalLineNumber    = LogicalLineNumber;
    Enode->Message              = MessageBuffer;

    AeAddToErrorLog (Enode);


    if (Gbl_DebugFlag)
    {
        /* stderr is a file, send error to it immediately */

        AePrintException (stderr, Enode);
    }


    Gbl_ExceptionCount[Level]++;

    if (Gbl_ExceptionCount[ASL_ERROR] > ASL_MAX_ERROR_COUNT)
    {

        AePrintErrorLog (stdout);
        if (Gbl_DebugFlag)
        {
            /* Print error summary to the debug file */

            AePrintErrorLog (stderr);
        }
        printf ("\nMaximum error count (%d) exceeded.\n", ASL_MAX_ERROR_COUNT);
        CmCleanupAndExit ();
    }


    return Enode;
}


/*******************************************************************************
 *
 * FUNCTION:    AslError
 *
 * PARAMETERS:  Level               - Seriousness (Warning/error, etc.)
 *              MessageId           - Index into global message buffer
 *              Node                - Parse node where error happened
 *              ExtraMessage        - additional error message
 *
 * RETURN:      None
 *
 * DESCRIPTION: Main error reporting routine for the ASL compiler (all code
 *              except the parser.)
 *
 ******************************************************************************/

void
AslError (
    UINT8                   Level,
    UINT8                   MessageId,
    ASL_PARSE_NODE          *Node,
    char                    *ExtraMessage)
{

    if (Node)
    {
        AslCommonError (Level, MessageId, Node->LineNumber,
                        Node->LogicalLineNumber, Node->Filename, ExtraMessage);
    }

    else
    {
        AslCommonError (Level, MessageId, 0,
                        0, NULL, ExtraMessage);
    }
}


/*******************************************************************************
 *
 * FUNCTION:    AslCompilererror
 *
 * PARAMETERS:  CompilerMessage
 *
 * RETURN:      Status?
 *
 * DESCRIPTION: Report an error situation discovered in a production
 *               NOTE: don't change the name of this function.
 *
 ******************************************************************************/

int
AslCompilererror (
    char                    *CompilerMessage)
{

    UINT32                  Length;


    Length = strlen (Gbl_InputFilename);

    if ((strlen (Gbl_CurrentLineBuffer) +
         strlen (CompilerMessage) +
         Length + Gbl_CurrentColumn + 9) >= ASL_MSG_BUFFER_SIZE)
    {
        strcpy (MsgBuffer, "Message Buffer Overflow");
    }

    else
    {
        sprintf (MsgBuffer, "%s\n%*s %s\n",
                    Gbl_CurrentLineBuffer,
                    Gbl_CurrentColumn + 14 + Length, "^",
                    CompilerMessage);
    }

    AslCommonError (ASL_ERROR, ASL_MSG_NULL, Gbl_CurrentLineNumber,
                    Gbl_LogicalLineNumber, Gbl_InputFilename, MsgBuffer);

    return 0;
}


