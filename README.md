# Crop 3D Binary Image
This repository contains code that crops a binary image based on its largest bounding box. It accepts 3D image files in formats such as NifTii, NRRD and GIPL. The only input required is the 3D image, the largest bounding box is computed automatically. 

## Dependencies
Note that this program uses [MIRTK - Medical Image Registration Library](https://github.com/BioMedIA/MIRTK) 

The dependencies are not great on MIRTK It is simply for accessing pixel values in the image. I envisage that the code can be easily ported into [Insight Toolkit](https://github.com/InsightSoftwareConsortium/ITK) and other imaging libraries. 

## Usage 
The usage for the first tool ```evaluate-image-crop``` if ``make`` installed under mirtk ``/lib/tools/``:
```
./mirtk evaluate-image-crop 
     -i <input binary image 0/1> 
     -o <output image file containing crop>
     -txt <output text file to write XYZ bounds>
```



## Author 
```
Dr. Rashed Karim 
Department of Biomedical Engineering 
King's College London 
```
