#!/bin/sh

# A routine to change the user that runs interbase Firebird


#------------------------------------------------------------------------
# Prompt for response, store result in Answer

Answer=""

AskQuestion() {
    Test=$1
    DefaultAns=$2
    echo -n "${1}"
    Answer="$DefaultAns"
    read Answer
}



#------------------------------------------------------------------------
# Check for a previous install 


checkInstallUser() {

    if [ "`whoami`" != "root" ];
      then
        ehco ""
        echo "--- Warning ----------------------------------------------"
        echo ""
        echo "    You need to be 'root' user to do this change"
        echo ""
        exit
    fi
}


#------------------------------------------------------------------------
#  check if it is running


checkIfServerRunning() {

# Check is server is being actively used.

    checkString=`ps -efww| egrep "(ibserver|ibguard)" |grep -v grep`

    if [ ! -z "$checkString" ] 
      then
        echo "An instance of the Firebird/InterBase Super server seems to be running." 
        echo "Please quit all interbase applications and then proceed"
        exit 1 
    fi

    checkString=`ps -efww| egrep "(gds_inet_server|gds_pipe)" |grep -v grep`

    if [ ! -z "$checkString" ] 
      then
        echo "An instance of the Firebird/InterBase server seems to be running." 
        echo "Please quit all interbase applications and then proceed." 
        exit 1 
    fi



# Stop lock manager if it is the only thing running.

    for i in `ps -efww | grep "gds_lock_mgr" | grep -v "grep" | awk '{print $2}' `
     do
        kill $i
     done

}


#------------------------------------------------------------------------
#  Add new user and group


addFirebirdUser() {

    groupadd -g 84 -o -r firebird

    useradd -o -r -m -d /home/firebird -s /bin/bash \
        -c "Firebird Database Administrator" -g firebird -u 84 firebird 

# >/dev/null 2>&1 
}


#------------------------------------------------------------------------
#  Delete new user and group


deleteFirebirdUser() {

    userdel firebird
 #   groupdel firebird

}



#------------------------------------------------------------------------
# add a service line in the (usually) /etc/services or /etc/inetd.conf file
# Here there are three cases, not found         => add service line,
#                             found & different => ask user to check
#                             found & same      => do nothing
#                             

replaceLineInFile() {
    FileName=$1
    newLine=$2
    oldLine=$3

    if [ -z "$oldLine" ] 
      then
        echo "$newLine" >> $FileName

    elif [ "$oldLine" != "$newLine"  ]
      then
# We really expect this to be the case.

        cat $FileName | grep -v "$oldLine" > ${FileName}.tmp
        mv ${FileName}.tmp $FileName
        echo "$newLine" >> $FileName
        echo "Updated."

    fi
}


IBRootDir=/opt/interbase
IBBin=$IBRootDir/bin




#RunUser=firebird
#RunGroup=firebird

# Well if you really insist, here it is ;-) - Mark.
#RunUser=interbase
#RunGroup=interbase



RunUser=root
RunGroup=root

checkInstallUser

checkIfServerRunning


echo ""
echo "Restore Firebird install for $IBRootDir to uid=$RunUser gid=$RunGroup"
echo "(User or group options can be changed by editing this script)"
echo ""
AskQuestion "Press return to continue - or ^C to abort"



# Update the /etc/inetd.conf
echo "Updating /etc/services file"


FileName=/etc/inetd.conf
newLine="gds_db  stream  tcp     nowait.30000      $RunUser $IBBin/gds_inet_server gds_inet_server # InterBase Database Remote Server"
oldLine=`grep "^gds_db" $FileName`

replaceLineInFile "$FileName" "$newLine" "$oldLine"



# Update ownership and SUID bits for programs.
echo "Updating $IBRootDir"


chown -R $RunUser.$RunGroup $IBRootDir

# Turn everybody to read only.
chmod -R o=r $IBRootDir

# Now fix up the mess.

# fix up directories 
for i in `find $IBRootDir -print`
  do
    FileName=$i
    if [ -d $FileName ]
       then
         chmod o=rx $FileName
     fi
  done



cd $IBBin

# all users can run everything.
chmod o=rx * 

# SUID is needed for running server programs.

for i in gds_lock_mgr gds_drop gds_inet_server
  do
    chmod ug+s $i
  done


cd $IBRootDir

# Lock files
# remember isc_guard1 in addition for super

cd $IBRootDir

for i in isc_init1 isc_lock1 isc_event1 
  do
    FileName=$i.`hostname`
    touch $FileName
    chmod uga=rw $FileName
  done


touch interbase.log
chmod ugo=rw interbase.log


# make databases writable by all
chmod ugo=rw examples/*.gdb
chmod ugo=rw help/*.gdb
chmod ugo=rw isc4.gdb



# Get inetd to reread new init files.

if [ -f /var/run/inetd.pid ]
  then
    kill -HUP `cat /var/run/inetd.pid`
fi


echo "Completed."