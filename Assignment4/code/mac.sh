qmake -project -o mac.pro
echo "QT += widgets" >> mac.pro
qmake mac.pro
make
