#include "mirtk/Common.h"
#include "mirtk/Options.h"
#include "mirtk/IOConfig.h"
#include "mirtk/GenericImage.h"

using namespace mirtk;

Array<double> i_ctr; 

void CropImage(GreyImage* img, char* crop_img_fn, char* crop_region_fn) {
	
	char *newfile;
	int minX=1E9, minY=1E9, minZ=1E9, maxX=-1, maxY=-1, maxZ=-1; 
	int minX_trunc, minY_trunc, minZ_trunc, maxX_trunc, maxY_trunc, maxZ_trunc;
	GreyImage cropped_img; 
  
  
  
	cout << "Wait while we truncate the image ...";
	for (int i=0;i<img->GetX();i++)
	{
		for (int j=0;j<img->GetY();j++)
		{
			for (int k=0;k<img->GetZ();k++)
			{
				if (img->Get(i,j,k) > 0)
				{
					//segmented_image.Put(i,j,k, 1); 
					if (i>maxX) { maxX = i;}
					if (j>maxY) { maxY = j;}
					if (k>maxZ) { maxZ = k;}
					if (i<minX) { minX = i;}
					if (j<minY) { minY = j;}
					if (k<minZ) { minZ = k;}
				}
			}
		}
	}

	// get the truncated ROI
	minX_trunc = max(0, minX); 
	minY_trunc = max(0, minY); 
	minZ_trunc = max(0, minZ); 
	maxX_trunc = min(img->GetX(), maxX); 
	maxY_trunc = min(img->GetY(), maxY); 
	maxZ_trunc = min(img->GetZ(), maxZ);

	// now extract the ROI - this is truncating the image to save hard-disk space, 
	// not extracting ROI using region-growing - that is different 
		
	cout << "Truncating completed .. now saving ... ";
	//segmented_image.Write(newfile);		
	// if you want to truncate, open the following comments up 
	cropped_img = img->GetRegion(minX_trunc, minY_trunc, minZ_trunc, maxX_trunc, maxY_trunc, maxZ_trunc);

	cropped_img.Write(crop_img_fn);	// if you dont want to truncate 
	//cout << "NOT TRUNCATING .. " << endl;
	cout << "TRUNCATING .. " << endl;
	//out.Write(newfile);					// if you want to truncate 

	cout << "Image saved !" << endl;
	cout << "region IMG NEW_IMG -Rx1 " << minX_trunc << " -Ry1 " << minY_trunc << " -Rz1 " << minZ_trunc << " -Rx2 " << maxX_trunc << " -Ry2 " << maxY_trunc << " -Rz2 " << maxZ_trunc << endl;

	if (crop_region_fn != "")
	{
		ofstream foutput; 
		foutput.open(crop_region_fn); 
		foutput << "region IMG NEW_IMG -Rx1 " << minX_trunc << " -Ry1 " << minY_trunc << " -Rz1 " << minZ_trunc << " -Rx2 " << maxX_trunc << " -Ry2 " << maxY_trunc << " -Rz2 " << maxZ_trunc << endl;
		foutput.close();
	}

  
	
}

int main(int argc, char **argv)
{
	int optind;
	bool foundArgs=false;
			
	GreyImage img1; 
	char* input_f="", *output_f="", *output_txt="";

	if (argc >= 1) 
	{
		int optind=1;
		
		while ((optind < argc) && (argv[optind][0]=='-')) {
			
			string sw = argv[optind];
			
			if (sw == "-i") {
				optind++;
				input_f = argv[optind]; 
				foundArgs = true;	
			}
			
			else if (sw == "-o") {
				optind++;
				output_f = argv[optind]; 
			}

			else if (sw == "-txt") {
				optind++;
				output_txt = argv[optind]; 
			}

						
			optind++; 
		}
	}
	
	if (foundArgs == false)
	{
		cout << "\n\nUsage: evaluate-image-crop.exe \n\n\t-i image> \n\t-o <output image> \n\t-txt <XYZ Bounds cropped region>" << endl; 
		exit(0); 
	}

	else
	{
		InitializeIOLibrary();
		//GreyImage img1(input_f1);
		//GreyImage img2(input_f2); 

		UniquePtr<BaseImage> img1(BaseImage::New(input_f));
		
		
		CropImage(new GenericImage<short>(*img1), output_f, output_txt);
		
	}

}
