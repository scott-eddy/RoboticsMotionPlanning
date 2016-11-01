#This is the build script for the project.  It generates build directory and makes the code from there

DebugBuild=true 
BuildDir=build

if [ -d "$BuildDir" ]; then
    rm -rf "$BuildDir"
    mkdir "$BuildDir"
else
    mkdir "$BuildDir"
fi

cd $BuildDir

if [ "$DebugBuild"=true ] ; then
    cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    cmake ..
fi

make -j8
