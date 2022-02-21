# Erstes gemeinsames Projekt 

<<<<<<< HEAD
In diesem Projekt geht es darum, ein Gerät zu entwickeln, das die Kommunikation in den Bergen ermöglicht.

## Status

| Radar  | Command                        			 			| Datum	| 
| -------| ---------------------------------------------------- | ----- | 
| V0.00  | `Start`      										| 18.01	|	
| V0.01  | `Implementierung der ersten `      					| 18.01	|	

## Detailstatus

### V0.00

- Erste Kommunikation getestet.
- Kommunikation [Link](https://arduino-projekte.webnode.at/meine-projekte/parametrieren-des-hc-12/)


### V0.01

- Implementierung der ersten Logik

## Tipps und Tricks 


### Arduino Nano nicht über USB-C

```
Es ist nicht möglich den Arduino Nano über USB-C zu flashen.
```

## Links

- Kommunikation [Link](https://arduino-projekte.webnode.at/meine-projekte/parametrieren-des-hc-12/)
=======
Hier werden wir Dokumentieren was wir machen

## Links die uns weiterhlefen 


- CPPYY empfohlen. [Link](http://wlav.web.cern.ch/wlav/Cppyy_LavrijsenDutta_PyHPC16.pdf)
- OpenCV empfohlen.
- [x] Python Literatur lesen
- [Python 3, 3836279266](https://www.amazon.de/dp/3836279266/ref=cm_sw_em_r_mt_dp_KDS1V4QH4GYDPSKPK4CT?_encoding=UTF8&psc=1)
- [x] Linux Literatur lesen
- [Ubuntu 18.04 LTS, 978-3-8362-6448-8](https://www.amazon.de/dp/383626448X/ref=cm_sw_em_r_mt_dp_7MACY1AFXSP23PF1PGAQ)
- [x] KI Literatur lesen


- [ ] Die art des Lernens aussuchen 
- Überwachtes lernen **(superweist learning)**

### Installation von Pytorch

Link zur Homepage
```
https://forums.developer.nvidia.com/t/pytorch-for-jetson-version-1-9-0-now-available/72048
```

Installationsablauf PyTorch
```
sudo apt-get install python3-pip libopenblas-base libopenmpi-dev 

sudo python3 -m pip install -U pip
sudo python3 -m pip install -U testresources
sudo python3 -m pip install -U setuptools 
sudo python3 -m pip install -U wheel
sudo python3 -m pip install -U numpy==1.19.4 Cython protobuf uff six pandas scipy
sudo python3 -m pip install -U matplotlib

wget https://nvidia.box.com/shared/static/2cqb9jwnncv9iii4u60vgd362x4rnkik.whl -O torch-1.9.0-cp36-cp36m-linux_aarch64.whl
sudo pip3 install torch-1.9.0-cp36-cp36m-linux_aarch64.whl 
```

Installationsablauf PyTorch Vision
```
sudo apt-get install libjpeg-dev zlib1g-dev libpython3-dev libavcodec-dev libavformat-dev libswscale-dev
sudo python3 -m pip install -U torchvision==0.10.0

```

Ausführen wenn nötig.
```
sudo apt-get install cuda-toolkit-10-2
sudo apt-get install libcudnn8

```
>>>>>>> agni
