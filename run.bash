makedirectory () {
    if [ ! -d "$1" ]; then
      echo "$1 does not exist."
      echo "Creating $1"
      mkdir $1
    else 
      echo "$1 does exist."
    fi
}

makedirectoryandCmake () {
    if [ ! -d "$1" ]; then
      echo "$1 does not exist."
      echo "Creating $1"
      mkdir $1 && cd $1
      cmake ..
      make 
      cd ..
    else 
      echo "$1 does exist."
    fi

}

BUILDDIR="build/"
PLOTDIR="plots/"

makedirectoryandCmake ${BUILDDIR}

echo "run the simulation..."
cd build/
./simulation run.mac
cd ..

makedirectory ${PLOTDIR}
count=0
echo "Analysing and plotting.."
for i in build/*.root
do 
    path=${i}
    root -l -q 'analysis.cpp('${count}', "'${path}'")'
    count=$((count+1))
done

