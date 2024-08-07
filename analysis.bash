makedirectory () {
    if [ ! -d "$1" ]; then
      echo "$1 does not exist."
      echo "Creating $1"
      mkdir $1
    else 
      echo "$1 does exist."
    fi
}

PLOTDIR="plots/"

makedirectory ${PLOTDIR}
count=0
echo "Analysing and plotting.."
for i in build/*.root
do 
    path=${i}
    root -l -q 'analysis.cpp('${count}', "'${path}'")'
    count=$((count+1))
done

