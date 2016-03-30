#include"chessman.h"
#include<QString>
#include<QImage>


chessman::chessman(chessman::ROLE roleplaying,chessman::Chessman_name chessman_name,QString argimagefilename1, QString argimagefilename2)
{

    imagefilename1 = argimagefilename1;
    imagefilename2 = argimagefilename2;
    if(!init_images())
    {
        qDebug()<<"init_images error";

    }

    setname(chessman_name);
    rolevalue = roleplaying;
    setdead(false);
}

chessman::chessman()
{

}

chessman::chessman(chessman &man)
{
    setname(man.name());
    setpower(man.power());
    pos = man.pos;
    image1 = man.image1;
    image2 = man.image2;
    image_to_show = &image1;
    imagefilename1 = man.imagefilename1;
    imagefilename2 = man.imagefilename2;
    setdead(man.isdead());
}

chessman::~chessman()
{

}

bool chessman::init_images()
{

    if( !(image1.load(imagefilename1) && image2.load(imagefilename2)) )
    {
        qDebug()<<"image1.load failed !!! .......";
        return false;
    }
    image_to_show = &image1;

    int i,j;

    for(i=0;i<40;i++)
    {
        for(j=0;j<40;j++)
        {
            if((i-20)*(i-20)+(j-20)*(j-20) > 19*19+30)
            {
                image2.setAlphaChannel(image2.createMaskFromColor(image1.pixel(i,j),Qt::MaskOutColor));
                image1.setAlphaChannel(image1.createMaskFromColor(image1.pixel(i,j),Qt::MaskOutColor));
            }
        }
    }
    return true;

}

const chessman::Chessman_name chessman::name()
{
    return chessmanname;
}





