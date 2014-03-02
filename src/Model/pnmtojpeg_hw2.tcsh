#!/dcs/bin/tcsh


# This script is specialized for eecs10 homework 7
# It takes one argument the file name (file stem only)
# - if ~/public_html does not exist, create it
# - file is moved to image.ppm
# - file is converted to jpg in ~/public_html
# -  chmod ~/public_html/<file>.jpg


# set the library path so that the pnmtojpg finds its libraries
#setenv LD_LIBRARY_PATH /dcs/packages/Xlocal/lib

# get the home directory, do not rely on variable HOME, it may
# not been set (who knows ...). use the cd command instead 
set HOME_DIR=`cd; pwd`
if ( $HOME_DIR == "" ) then
    echo Failed to get home directory
    if ( -d ../public_html ) then
	echo Assume: ../public_html
	set HTML_DIR="../public_html"
    else 
	exit 1
    endif
else
    # dir to place converted pictures 
    set HTML_DIR="$HOME_DIR/public_html"
endif 


# get just the file name of the second argument
set T_FNAME=`basename $1 .ppm`

# move input name to a fixed name
# allows investigating last image, but overwrites all others
#if ( -r $1 ) then
#else
#    echo Can not read: $1 
#    exit 1
#endif

#if ($1 != "image.ppm") then 
#   mv $1 image.ppm
#endif

# test if public html directory is there 
if ( -r $HTML_DIR ) then
    if( -r $HTML_DIR/index.html) then
	cmp $HTML_DIR/index.html /users/grad2/doemer/eecs22/hw4/index.html -s
	if($status) then
	    cp /users/grad2/doemer/eecs22/hw4/index.html $HTML_DIR
	else
	endif    
    else
       echo "Creating $HTML_DIR/index.html" 
       cp /users/grad2/doemer/eecs22/hw4/index.html $HTML_DIR
       chmod -R 755 $HTML_DIR 
    endif # added by weiweic 11/15/2010
else
    echo "$HTML_DIR does not exist, creating it."
    mkdir $HTML_DIR
    cp /users/grad2/doemer/eecs22/hw4/index.html $HTML_DIR
    chmod -R 755 $HTML_DIR
endif

if( -r $HTML_DIR/UCI_Peter.jpg) then
else
#    /dcs/packages/Xlocal/bin/pnmtojpeg UCI_Peter.ppm > $HTML_DIR/UCI_Peter.jpg
    /usr/bin/pnmtojpeg UCI_Peter.ppm > $HTML_DIR/UCI_Peter.jpg
    chmod 644 $HTML_DIR/UCI_Peter.jpg
endif

# call the converstion 
#/dcs/packages/Xlocal/bin/pnmtojpeg image.ppm > $HTML_DIR/$T_FNAME.jpg
#/dcs/packages/Xlocal/bin/pnmtojpeg $1 > $HTML_DIR/$T_FNAME.jpg
/usr/bin/pnmtojpeg $1 > $HTML_DIR/$T_FNAME.jpg

# ensure file is readable to the world (so that httpd will pick it up)
chmod 644 $HTML_DIR/$T_FNAME.jpg










