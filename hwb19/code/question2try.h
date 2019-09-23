//方案尝试1：对图像坐标系中的点按到原点距离排序，取前3个点匹配观察匹配数量
//实验结果：可匹配数量太多
inline Position calp2try1(StarImg* xtt,int len,const double& f){
    StarImg xt[50];
    for(int i=0;i<len;++i)xt[i]=xtt[i];
    double eps=1e-3;
    StarMap zb[50];
    sort(xt,xt+len);
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    vector<vector<int> > ans,next;
    vector<int> tmp;
    double angx=oang(zb[0],zb[1]);
    int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
    for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    printf("size=%d\n",ans.size());
    double anga=oang(zb[0],zb[2]),angb=oang(zb[1],zb[2]);
    for(int i=0;i<ans.size();++i){
        int pa=ans[i][0],pb=ans[i][1];
        int fid=lower_bound(angsort[pa],angsort[pa]+N-1,PointPair(0,0,anga))-angsort[pa];
        for(int j=fid;j<N-1&&fabs(angsort[pa][j].ang-anga)<eps;++j){
            int add=angsort[pa][j].b;
            if(fabs(ang[add][pb]-angb)<eps){
                next.push_back(ans[i]);
                next.back().push_back(add);
            }
        }
        for(int j=fid-1;j>=0&&fabs(angsort[pa][j].ang-anga)<eps;--j){
            int add=angsort[pa][j].b;
            if(fabs(ang[add][pb]-angb)<eps){
                next.push_back(ans[i]);
                next.back().push_back(add);
            }
        }
    }
    printf("size=%d\n",next.size());
    ans=next;
    next.clear();
//    for(int i=0;i<ans.size();++i){
//        for(int j=0;j<3;++j){
//            printf("%d ",ans[i][j]);
//        }
//        printf("\n");
//    }
}
//方案尝试2：对图像坐标系中的点按到原点距离排序，不断添加点
//实验结果：没有完全匹配的方法，考虑到可能由于假星的干扰导致
inline Position calp2try2(StarImg* xtt,int len,const double& f){
    StarImg xt[50];
    for(int i=0;i<len;++i)xt[i]=xtt[i];
    double eps=1e-2;
    StarMap zb[50];
    sort(xt,xt+len);
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    vector<vector<int> > ans,next;
    vector<int> tmp;
    double angx=oang(zb[0],zb[1]);
    int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
    for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
        tmp.clear();
        tmp.push_back(pp[i].a);
        tmp.push_back(pp[i].b);
        ans.push_back(tmp);
    }
    printf("size=%d\n",ans.size());
    for(int z=2;z<len;++z){
        double angy[50];
        for(int i=0;i<z;++i)angy[i]=oang(zb[i],zb[z]);
        for(int i=0;i<ans.size();++i){
            int pa=ans[i][0];
            int fid=lower_bound(angsort[pa],angsort[pa]+N-1,PointPair(0,0,angy[0]))-angsort[pa];
            for(int j=fid;j<N-1&&fabs(angsort[pa][j].ang-angy[0])<eps;++j){
                int add=angsort[pa][j].b;
                bool check=true;
                for(int c=1;c<z;++c){
                    if(fabs(ang[add][ans[i][c]]-angy[c])>=eps){
                        check=false;
                        break;
                    }
                }
                if(check){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                }
            }
            for(int j=fid-1;j>=0&&fabs(angsort[pa][j].ang-angy[0])<eps;--j){
                int add=angsort[pa][j].b;
                int c=1;
                bool check=true;
                for(int c=1;c<z;++c){
                    if(fabs(ang[add][ans[i][c]]-angy[c])>=eps){
                        check=false;
                        break;
                    }
                }
                if(check){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                }
            }
        }
        printf("z=%d size=%d\n",z,next.size());
        ans=next;
        next.clear();
    }
//    for(int i=0;i<ans.size();++i){
//        for(int j=0;j<len;++j){
//            printf("%d ",ans[i][j]);
//        }
//        printf("\n");
//    }
}
//方案尝试3：从图像坐标系中任意选择3点组合匹配避免假星影响，确定星敏感器方向，根据其它星的匹配距离确定误差
//实验结果：发现3个角度匹配产生的镜面对称情况，用其它星点匹配距离确定误差无法充分利用数据库星等和邻域信息
inline Position calp2try3(StarImg* xt,int len,const double& f){
    double eps=1e-4,eps2=1e-3;
    StarMap zb[50];
    for(int i=0;i<len;++i)zb[i]=itox(xt[i],f);
    vector<vector<int> > ret;
    for(int aa=0;aa<len;++aa)for(int bb=aa+1;bb<len;++bb)for(int cc=bb+1;cc<len;++cc){
        vector<vector<int> > ans,next;
        vector<int> tmp;
        double angx=oang(zb[aa],zb[bb]);
        int fid=lower_bound(pp,pp+PN,PointPair(0,0,angx))-pp;
        for(int i=fid;i<PN&&pp[i].ang-angx<eps;++i){
            tmp.clear();
            tmp.push_back(pp[i].a);
            tmp.push_back(pp[i].b);
            ans.push_back(tmp);
        }
        for(int i=fid-1;i>=0&&angx-pp[i].ang<eps;--i){
            tmp.clear();
            tmp.push_back(pp[i].a);
            tmp.push_back(pp[i].b);
            ans.push_back(tmp);
        }
        double anga=oang(zb[aa],zb[cc]),angb=oang(zb[bb],zb[cc]);
        for(int i=0;i<ans.size();++i){
            int pa=ans[i][0],pb=ans[i][1];
            int fid=lower_bound(angsort[pa],angsort[pa]+N-1,PointPair(0,0,anga))-angsort[pa];
            for(int j=fid;j<N-1&&fabs(angsort[pa][j].ang-anga)<eps;++j){
                int add=angsort[pa][j].b;
                if(fabs(ang[add][pb]-angb)<eps){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                    next.back().push_back(aa);
                    next.back().push_back(bb);
                    next.back().push_back(cc);
                }
            }
            for(int j=fid-1;j>=0&&fabs(angsort[pa][j].ang-anga)<eps;--j){
                int add=angsort[pa][j].b;
                if(fabs(ang[add][pb]-angb)<eps){
                    next.push_back(ans[i]);
                    next.back().push_back(add);
                    next.back().push_back(aa);
                    next.back().push_back(bb);
                    next.back().push_back(cc);
                }
            }
        }
        ans=next;
        next.clear();
        for(int i=0;i<ans.size();++i)ret.push_back(ans[i]);
        ans.clear();
    }
    printf("size=%d\n",ret.size());
    vector<double> val;
    val.resize(ret.size());
    int choose[50],chnow[50];
    double wc[50],wcnow[50];
    double eval2=1e100;
    int eval=-1,err=0;
    for(int i=0;i<ret.size();++i){
        if(i%1000==0)printf("i=%d\n",i);
        double enow2=0;
        int enow=0;
        int ta=ret[i][0],tb=ret[i][1],tc=ret[i][2];
        int aa=ret[i][3],bb=ret[i][4],cc=ret[i][5];
        Position ret=calp11(mp[ta],mp[tb],mp[tc],xt[aa].dis(),xt[bb].dis(),xt[cc].dis(),f).toPosition();
        StarImg p1=mtoi(mp[ta],ret,f);
        StarImg p2=mtoi(mp[tb],ret,f);
        StarImg p3=mtoi(mp[tc],ret,f);
        double rg1=imgang(p1,xt[aa]);
        double rg2=imgang(p2,xt[bb]);
        double rg3=imgang(p3,xt[cc]);
        if(argdis(rg1,rg2)>CH||argdis(rg1,rg3)>CH||argdis(rg2,rg3)>CH){
            ++err;
            continue;
        }
//        printf("%f %f %f\n",rg1,rg2,rg3);
//        printf("%f\n",ret.rot);
//        p1.printfx();
//        p2.printfx();
//        p3.printfx();
//        xt[aa].printfx();
//        xt[bb].printfx();
//        xt[cc].printfx();
        ret.rot=(rg1+rg2+rg3)/3;
        val[i]=0;
//        printf("%d %d %d\n",ta,tb,tc);
//        mp[ta].printfx();
//        mp[tb].printfx();
//        mp[tc].printfx();
        for(int j=0;j<len;++j){
            StarMap xx=itox(xt[j],f);
            xx=xtom(xx,ret).toMap();
//            xx.printfx();
            wcnow[j]=1e100;
            chnow[j]=-1;
            for(int k=0;k<N;++k){
                if(xx.check(mp[k])){
                    double now=oang(xx,mp[k]);
                    if(now<wcnow[j])wcnow[j]=now,chnow[j]=k;
                }
            }
            if(wcnow[j]<eps2)enow2=max(enow2,wcnow[j]);
            if(wcnow[j]<eps2)++enow;
        }
//        if(enow<eval){
        if(enow>eval||enow==eval&&enow2<eval2){
            eval=enow;
            eval2=enow2;
            for(int j=0;j<len;++j)choose[j]=chnow[j],wc[j]=wcnow[j];
        }
    }
    printf("err=%d\ncnt=%d val=%f\n",err,eval,eval2);
    for(int i=0;i<len;++i){
        printf("%d %f\n",choose[i],wc[i]);
    }
}
