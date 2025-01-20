/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>

#include <cassert>

using namespace std;


    /********************************
    Mejora del Contraste
    ********************************/

    void Image::AdjustContrast (byte in1, byte in2, byte out1, byte out2){
        double cociente0 = (double)(out1) / (double)(in1);
        double cociente1 = (double)(out2 - out1) / (double)(in2 - in1);
        double cociente2 = (double)(255 - out2) / (double)(255 - in2);

        for (int k=0; k<rows*cols; k++){
            byte val = get_pixel(k);
            if      (val < in1)    val = round(0  + cociente0 * (val - 0));
            else if (val > in2)    val = round(out2 + cociente2 * (val - in2));
            else                  val = round(out1 + cociente1 * (val - in1));
            set_pixel(k,val);
        }

        //    for (Image::Iterator it = begin(); it != end(); it++){
        //    for (unsigned char & val : *this){
        //        if      (val < in1) val = round(0 + cociente0 * (val - 0));
        //        else if (val > in2) val = round(out2 + cociente2 * (val - in2));
        //        else                  val = round(out1 + cociente1 * (val - in1));
        //    }

    }



    /********************************
    Subsample
    *********************************/

    double Image::Mean(int init_i, int init_j, int height, int width) const {
        assert ((init_i >= 0) && (init_j >= 0) && (height > 0) && (width > 0));

        double suma = 0;

        for (int i=init_i; i < height + init_i; i++)
            for (int j=init_j; j < width + init_j; j++)
                suma += get_pixel(i,j);

            return suma/(height*width);
    }

    Image Image::Subsample(int factor) const{
        assert (factor > 0);

        Image icono(floor(rows / factor), floor(cols / factor));

        for (int i=0; i<icono.rows; i++)
            for (int j=0; j<icono.cols; j++)
                icono.set_pixel(i,j, (byte) round(Mean(i * factor, j * factor, factor, factor)));

            return icono;
    }



    Image Image::Crop(int nrow, int ncol, int height, int width) const{
        //    assert ((nrow >= 0) && (ncol >= 0) && (height > 0) && (width > 0));
        Image subimagen(height, width);

        int i,j;
        for (i=0; i<height; i++)
            for (j=0; j<width; j++){
                subimagen.set_pixel(i, j, get_pixel(nrow + i, ncol + j));
            }

        return subimagen;
    }

    Image Image::Zoom2X() const {
        int zrows = rows * 2 - 1;
        int zcols = cols * 2 - 1;
        Image zoom(zrows,zcols);

        int ri,rj;
        double b;
        for (int i=0; i<zrows; i++)
            for (int j=0; j<zcols; j++){
                ri = i/2;
                rj = j/2;

                // center case
                if ((i%2 == 0) && (j%2 == 0))
                    b = this->get_pixel(ri,rj) ;
                // corner case
                else if ((i%2 == 1) && (j%2 == 1)){
                    b =  this->get_pixel(ri,rj);
                    b += this->get_pixel(ri,rj+1);
                    b += this->get_pixel(ri+1,rj);
                    b += this->get_pixel(ri+1,rj+1) ;
                    b /= 4;
                }
                // vertical case
                else if (i%2 == 0){
                    b =  this->get_pixel(ri,rj);
                    b += this->get_pixel(ri,rj+1);
                    b /= 2;
                }
                // horizontal case
                else{
                    b =  this->get_pixel(ri,rj);
                    b += this->get_pixel(ri+1,rj);
                    b /= 2;
                }

                zoom.set_pixel(i,j,(byte) round(b));
            }


        return zoom;
    }

    void Image::PaintIn(Image & in, int init_i, int init_j){
        for (int i=init_i, i_ref=0; i < rows && i_ref < in.rows; i++, i_ref++)
            for (int j=init_j, j_ref=0; j < cols && j_ref < in.cols; j++, j_ref++)
                set_pixel(i, j, in.get_pixel(i_ref, j_ref));
    }

