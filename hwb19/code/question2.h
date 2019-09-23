struct match{
    int ta,tb,tc,aa,bb,cc;
};
match mlist[500010];
int paira[10010],pairb[10010],pairnum,mnum;
inline Position calp2(StarImg* xt,int len,int xtid){
    double f=xtid<7?f1:f2;
    double fang=xtid<7?ANG1:ANG2;
    double djx=xtid<7?512*sqrt(2):1024*sqrt(2);
    double bjp=xtid<7?307.5:563.5;
    double eps=1e-3;
    StarMap zb[50];
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    double xtang[50][50];
    for(int i=0;i<len;++i)for(int j=i+1;j<len;++j)xtang[i][j]=oang(zb[i],zb[j]);
    mnum=0;
    for(int aa=0;aa<len;++aa){
        for(int bb=aa+1;bb<len;++bb){
            for(int cc=bb+1;cc<len;++cc){
                pairnum=0;
                double &angx=xtang[aa][bb];
                int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
                for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
                    paira[pairnum]=pp[i].a;
                    pairb[pairnum++]=pp[i].b;
                }
                for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
                    paira[pairnum]=pp[i].a;
                    pairb[pairnum++]=pp[i].b;
                }
                double &anga=xtang[aa][cc];
                double &angb=xtang[bb][cc];
                for(int i=0;i<pairnum;++i){
                    int fid=lower_bound(angsort[paira[i]],angsort[paira[i]]+N-1,PointPair(0,0,anga))-angsort[paira[i]];
                    for(int j=fid;j<N-1&&fabs(angsort[paira[i]][j].ang-anga)<eps;++j){
                        int add=angsort[paira[i]][j].b;
                        if(fabs(ang[add][pairb[i]]-angb)<eps){
                            mlist[mnum++]=(match){paira[i],pairb[i],add,aa,bb,cc};
                        }
                    }
                    for(int j=fid-1;j>=0&&fabs(angsort[paira[i]][j].ang-anga)<eps;--j){
                        int add=angsort[paira[i]][j].b;
                        if(fabs(ang[add][pairb[i]]-angb)<eps){
                            mlist[mnum++]=(match){paira[i],pairb[i],add,aa,bb,cc};
                        }
                    }
                }
            }
        }
    }
    printf("find 3-pair point size=%d\n",mnum);
    int err=0,picid[400],nowid[50],rfail=100,rid[50],rpicid[400],rcc;
    StarImg pic[400],nowzb[50],rzb[50],rpic[400];
    bool picbj[400],rpicbj[400];
    double nowdis[50],rpgz=1e100,rdis[50];
    Position rret;
    for(int i=0;i<mnum;++i){
        Position ret=calp11(mp[mlist[i].ta],mp[mlist[i].tb],mp[mlist[i].tc],xt[mlist[i].aa].dis(),xt[mlist[i].bb].dis(),xt[mlist[i].cc].dis(),f).toPosition();
        StarImg p1=mtoi(mp[mlist[i].ta],ret,f);
        StarImg p2=mtoi(mp[mlist[i].tb],ret,f);
        StarImg p3=mtoi(mp[mlist[i].tc],ret,f);
        double rg1=imgang(p1,xt[mlist[i].aa]);
        double rg2=imgang(p2,xt[mlist[i].bb]);
        double rg3=imgang(p3,xt[mlist[i].cc]);
        if(argdis(rg1,rg2)>CH||argdis(rg1,rg3)>CH||argdis(rg2,rg3)>CH){
            ++err;
            continue;
        }
        double pgz=0;
        int fail=0,cc=0;
        ret.rot=(rg1+rg2+rg3)/3;
        int xlen=lower_bound(angsort[mlist[i].ta],angsort[mlist[i].ta]+N-1,PointPair(0,0,fang))-angsort[mlist[i].ta];
        for(int j=0;j<xlen;++j){
            picid[cc]=angsort[mlist[i].ta][j].b;
            pic[cc]=mtoi(mp[picid[cc]],ret,f);
            if(pic[cc].x>=-bjp&&pic[cc].x<=bjp&&pic[cc].y>=-bjp&&pic[cc].y<=bjp)picbj[cc]=false,++cc;
        }
        for(int k=0;k<len;++k){
            double mx=1e100;
            int mid=-1;
            for(int j=0;j<cc;++j){
                if(picbj[j])continue;
                double td=pic[j].pdis(xt[k]);
                if(td<mx)mx=td,mid=j;
            }
            if(mx<50){
                picbj[mid]=true;
                nowid[k]=picid[mid];
                nowdis[k]=mx;
                nowzb[k]=pic[mid];
                pgz+=pow(2.5,-mp[picid[mid]].l)*mx/djx;
            }else{
                nowid[k]=-1;
                nowdis[k]=-1;
                pgz+=avg;
                ++fail;
            }
        }
        for(int j=0;j<cc;++j){
            if(!picbj[j]&&pic[j].x>=-bjp+51.5&&pic[j].x<=bjp-51.5&&pic[j].y>=-bjp+51.5&&pic[j].y<=bjp-51.5){
                pgz+=pow(2.5,-mp[picid[j]].l);
            }
        }
        if(fail<rfail||fail==rfail&&pgz<rpgz){
            rfail=fail;
            rpgz=pgz;
            rret=ret;
            rcc=cc;
            for(int j=0;j<len;++j)rid[j]=nowid[j],rdis[j]=nowdis[j],rzb[j]=nowzb[j];
            for(int j=0;j<cc;++j)rpic[j]=pic[j],rpicid[j]=picid[j],rpicbj[j]=picbj[j];
        }
    }
    printf("error find %d\nfail=%d val=%f\n",err,rfail,rpgz);
    for(int i=0;i<len;++i){
        printf("%d error=%f\n",rid[i],rdis[i]);
    }
    printf("position:ew=%f ns=%f rot=%f\n",rret.ew,rret.ns,rret.rot);
    char name[20]="draw_xt?.m";
    name[7]=xtid+48;
    FILE *fp=fopen(name,"w");
    fprintf(fp,"plot3(0,0,0,'.b')\n");
    fprintf(fp,"hold on\n");
    fprintf(fp,"x=[-%.0f,%.0f;-%.0f,%.0f];\n",bjp-51.5,bjp-51.5,bjp-51.5,bjp-51.5);
    fprintf(fp,"y=[-%.0f,-%.0f;%.0f,%.0f];\n",bjp-51.5,bjp-51.5,bjp-51.5,bjp-51.5);
    fprintf(fp,"z=[%f,%f;%f,%f];\n",f,f,f,f);
    fprintf(fp,"surf(x,y,z)\n",f,f,f,f);
    fprintf(fp,"alpha(0.3)\n",f,f,f,f);
    for(int i=0;i<len;++i){
        fprintf(fp,"plot3(%f,%f,%f,'.b')\n",xt[i].x,xt[i].y,f);
        fprintf(fp,"hold on\n");
        if(rid[i]!=-1){
            fprintf(fp,"x=linspace(%f,%f,10000);\n",xt[i].x,rzb[i].x);
            fprintf(fp,"y=linspace(%f,%f,10000);\n",xt[i].y,rzb[i].y);
            fprintf(fp,"z=linspace(%f,%f,10000);\n",f,f);
            fprintf(fp,"plot3(x,y,z,'b')\n");
            fprintf(fp,"hold on\n");
        }
    }
    for(int i=0;i<rcc;++i){
        fprintf(fp,"plot3(%f,%f,%f,'.r','markersize',%f)\n",rpic[i].x,rpic[i].y,f,13-mp[rpicid[i]].l);
        fprintf(fp,"hold on\n");
        StarZB tmp;
        tmp.x=rpic[i].x;
        tmp.y=rpic[i].y;
        tmp.z=f;
        tmp=tmp.toMap().toZB();
        fprintf(fp,"plot3(%f,%f,%f,'.r','markersize',%f)\n",tmp.x*f*3,tmp.y*f*3,tmp.z*f*3,17-mp[rpicid[i]].l);
        fprintf(fp,"hold on\n");
        if(rpicbj[i]){
            fprintf(fp,"x=linspace(0,%f,10000);\n",tmp.x*f*3);
            fprintf(fp,"y=linspace(0,%f,10000);\n",tmp.y*f*3);
            fprintf(fp,"z=linspace(0,%f,10000);\n",tmp.z*f*3);
            fprintf(fp,"plot3(x,y,z,'b')\n");
            fprintf(fp,"hold on\n");
        }
    }
    fclose(fp);
}
