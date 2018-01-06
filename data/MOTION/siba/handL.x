xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 64;
 1.87383;0.08973;0.39620;,
 2.08027;0.11053;0.10522;,
 1.87742;0.26274;0.31878;,
 1.69654;-0.20582;0.27862;,
 1.89652;0.02959;0.08279;,
 1.68903;-0.01049;0.38882;,
 1.71057;-0.26518;0.04381;,
 1.72282;-0.15375;-0.17809;,
 1.72621;0.06316;-0.25712;,
 1.90238;0.31219;-0.11492;,
 1.90912;0.15964;-0.21696;,
 1.88917;0.36855;0.10807;,
 -0.25849;0.06496;0.07903;,
 -0.22943;-0.08740;-0.11405;,
 -0.23018;-0.10334;0.14402;,
 -0.19273;-0.25342;0.05929;,
 -0.16846;-0.29826;-0.12479;,
 -0.17197;-0.21231;-0.30132;,
 -0.20073;-0.04501;-0.36762;,
 -0.23760;0.10634;-0.28394;,
 -0.26142;0.15217;-0.09855;,
 1.69252;0.20641;0.30985;,
 1.56266;-0.01436;0.39871;,
 1.56632;0.21671;0.31459;,
 1.57066;-0.22243;0.28133;,
 1.58554;-0.28561;0.03120;,
 1.59866;-0.16696;-0.20518;,
 1.60226;0.06410;-0.28937;,
 1.71881;0.25849;-0.14697;,
 1.59433;0.27219;-0.17202;,
 1.70496;0.31782;0.08791;,
 1.57962;0.33538;0.07818;,
 0.38968;0.31186;0.38713;,
 -0.18246;0.18418;0.22845;,
 0.38375;-0.07784;0.52904;,
 -0.13661;-0.10708;0.34177;,
 -0.18651;0.33442;-0.07798;,
 0.41169;0.51206;-0.01153;,
 0.43690;0.40541;-0.43337;,
 -0.14640;0.25561;-0.39804;,
 0.45053;0.05444;-0.63126;,
 -0.08562;-0.00607;-0.54423;,
 0.44459;-0.33523;-0.48930;,
 -0.03978;-0.29733;-0.43092;,
 0.42259;-0.53540;-0.09069;,
 -0.03573;-0.44757;-0.12448;,
 -0.07584;-0.36876;0.19558;,
 0.39738;-0.42877;0.33110;,
 1.32473;-0.02182;0.41749;,
 1.32875;0.23600;0.32362;,
 1.33369;-0.25400;0.28652;,
 1.35032;-0.32452;0.00743;,
 1.36493;-0.19211;-0.25631;,
 1.36891;0.06570;-0.35024;,
 1.36000;0.29790;-0.21932;,
 1.34349;0.36843;0.05984;,
 1.18867;0.18720;0.26644;,
 1.18525;-0.03216;0.34630;,
 1.20119;0.29987;0.04202;,
 1.21526;0.23986;-0.19548;,
 1.22285;0.04231;-0.30687;,
 1.21946;-0.17703;-0.22696;,
 1.20704;-0.28968;-0.00257;,
 1.19288;-0.22969;0.23487;;
 
 124;
 3;0,1,2;,
 3;3,4,5;,
 3;6,4,3;,
 3;7,4,6;,
 3;8,4,7;,
 3;9,1,10;,
 3;11,1,9;,
 3;2,1,11;,
 3;12,13,14;,
 3;14,13,15;,
 3;15,13,16;,
 3;16,13,17;,
 3;17,13,18;,
 3;18,13,19;,
 3;19,13,20;,
 3;20,13,12;,
 3;5,21,22;,
 3;21,23,22;,
 3;3,5,24;,
 3;5,22,24;,
 3;6,3,25;,
 3;3,24,25;,
 3;6,25,7;,
 3;25,26,7;,
 3;7,26,8;,
 3;26,27,8;,
 3;8,27,28;,
 3;27,29,28;,
 3;28,29,30;,
 3;29,31,30;,
 3;30,31,21;,
 3;31,23,21;,
 3;32,33,34;,
 3;33,35,34;,
 3;33,32,36;,
 3;32,37,36;,
 3;37,38,36;,
 3;38,39,36;,
 3;38,40,39;,
 3;40,41,39;,
 3;40,42,41;,
 3;42,43,41;,
 3;42,44,43;,
 3;44,45,43;,
 3;45,44,46;,
 3;44,47,46;,
 3;46,47,35;,
 3;47,34,35;,
 3;22,23,48;,
 3;23,49,48;,
 3;24,22,50;,
 3;22,48,50;,
 3;24,50,25;,
 3;50,51,25;,
 3;25,51,26;,
 3;51,52,26;,
 3;26,52,27;,
 3;52,53,27;,
 3;27,53,29;,
 3;53,54,29;,
 3;29,54,31;,
 3;54,55,31;,
 3;31,55,23;,
 3;55,49,23;,
 3;36,20,33;,
 3;20,12,33;,
 3;36,39,20;,
 3;39,19,20;,
 3;39,41,19;,
 3;41,18,19;,
 3;41,43,18;,
 3;43,17,18;,
 3;43,45,17;,
 3;45,16,17;,
 3;46,15,45;,
 3;15,16,45;,
 3;35,14,46;,
 3;14,15,46;,
 3;33,12,35;,
 3;12,14,35;,
 3;5,0,21;,
 3;0,2,21;,
 3;5,4,0;,
 3;4,1,0;,
 3;8,28,10;,
 3;28,9,10;,
 3;8,10,4;,
 3;10,1,4;,
 3;28,30,9;,
 3;30,11,9;,
 3;21,2,30;,
 3;2,11,30;,
 3;49,56,48;,
 3;56,57,48;,
 3;55,58,49;,
 3;58,56,49;,
 3;55,54,58;,
 3;54,59,58;,
 3;54,53,59;,
 3;53,60,59;,
 3;53,52,60;,
 3;52,61,60;,
 3;52,51,61;,
 3;51,62,61;,
 3;50,63,51;,
 3;63,62,51;,
 3;48,57,50;,
 3;57,63,50;,
 3;58,37,56;,
 3;37,32,56;,
 3;58,59,37;,
 3;59,38,37;,
 3;59,60,38;,
 3;60,40,38;,
 3;60,61,40;,
 3;61,42,40;,
 3;61,62,42;,
 3;62,44,42;,
 3;63,47,62;,
 3;47,44,62;,
 3;57,34,63;,
 3;34,47,63;,
 3;56,32,57;,
 3;32,34,57;;
 
 MeshMaterialList {
  1;
  124;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\MOTION\\siba\\UV02.png";
   }
  }
 }
 MeshNormals {
  74;
  -0.056444;0.628906;0.775430;,
  0.305835;-0.441228;0.843672;,
  0.460290;-0.745573;0.481927;,
  0.564619;-0.823333;-0.057692;,
  0.531820;-0.636900;-0.558144;,
  0.351191;0.028591;-0.935867;,
  0.051647;0.709532;-0.702778;,
  -0.098311;0.993946;0.049055;,
  -0.978314;0.019035;0.206249;,
  -0.938240;-0.251350;0.237760;,
  -0.880424;-0.466056;0.087437;,
  -0.872857;-0.476644;-0.104554;,
  -0.850234;-0.438449;-0.291314;,
  -0.893159;-0.204514;-0.400551;,
  -0.947275;0.060675;-0.314626;,
  -0.976228;0.214232;-0.032930;,
  0.720085;-0.693107;-0.032865;,
  -0.976760;-0.199250;-0.078988;,
  0.081986;0.660344;0.746475;,
  0.080671;-0.080617;0.993475;,
  0.111498;-0.731480;0.672685;,
  0.166470;-0.985021;-0.044965;,
  0.227669;-0.653750;-0.721649;,
  0.251868;0.081894;-0.964290;,
  0.204249;0.784504;-0.585522;,
  0.128896;0.984878;0.115761;,
  -0.703435;0.420242;0.573215;,
  -0.063393;0.663368;0.745603;,
  0.071501;0.991005;0.113121;,
  -0.559290;0.826960;0.057717;,
  0.053287;0.794502;-0.604919;,
  -0.628779;0.528704;-0.570183;,
  0.112069;0.077079;-0.990707;,
  -0.549909;-0.080013;-0.831383;,
  0.112817;-0.668422;-0.735176;,
  -0.484496;-0.642074;-0.594142;,
  -0.012772;-0.993860;-0.109906;,
  -0.584804;-0.801659;-0.123881;,
  -0.001332;-0.799480;0.600691;,
  -0.571676;-0.725858;0.382514;,
  -0.056228;-0.089027;0.994441;,
  -0.669468;-0.202346;0.714751;,
  0.789202;0.409001;0.458125;,
  0.783528;0.240185;0.573057;,
  0.877750;0.467279;0.105853;,
  0.858128;0.311128;-0.408432;,
  0.847373;0.462262;-0.261293;,
  0.799005;0.590529;0.113430;,
  -0.199330;0.065705;0.977727;,
  -0.260759;0.701525;0.663225;,
  -0.111067;0.977847;0.177426;,
  -0.108463;0.863892;-0.491860;,
  -0.032969;0.228285;-0.973036;,
  0.007330;-0.562612;-0.826689;,
  -0.052716;-0.984894;-0.164940;,
  -0.088925;-0.757973;0.646196;,
  -0.140368;0.664492;0.733994;,
  -0.223606;0.970210;0.093231;,
  -0.029279;0.794674;-0.606330;,
  0.057677;0.079305;-0.995180;,
  0.084876;-0.667084;-0.740132;,
  0.133314;-0.986006;-0.100099;,
  -0.029771;-0.796598;0.603776;,
  -0.114588;-0.082363;0.989993;,
  0.063064;0.340508;0.938124;,
  -0.193314;0.371587;0.908049;,
  -0.257917;0.749604;0.609568;,
  0.418124;-0.886029;0.200314;,
  0.409768;-0.908979;-0.076463;,
  -0.041915;0.522337;-0.851708;,
  -0.170264;0.864263;-0.473349;,
  0.496081;-0.803953;-0.327970;,
  0.455140;-0.823673;-0.338246;,
  -0.273453;0.957815;0.088400;;
  124;
  3;43,44,42;,
  3;2,16,1;,
  3;3,16,2;,
  3;4,16,3;,
  3;5,16,4;,
  3;46,44,45;,
  3;47,44,46;,
  3;42,44,47;,
  3;8,17,9;,
  3;9,17,10;,
  3;10,17,11;,
  3;11,17,12;,
  3;12,17,13;,
  3;13,17,14;,
  3;14,17,15;,
  3;15,17,8;,
  3;64,0,19;,
  3;0,18,19;,
  3;2,1,20;,
  3;1,19,20;,
  3;3,2,21;,
  3;2,20,21;,
  3;3,21,4;,
  3;21,22,4;,
  3;4,22,5;,
  3;22,23,5;,
  3;5,23,6;,
  3;23,24,6;,
  3;6,24,7;,
  3;24,25,7;,
  3;7,25,0;,
  3;25,18,0;,
  3;27,26,40;,
  3;26,41,40;,
  3;26,27,29;,
  3;27,28,29;,
  3;28,30,29;,
  3;30,31,29;,
  3;30,32,31;,
  3;32,33,31;,
  3;32,34,33;,
  3;34,35,33;,
  3;34,36,35;,
  3;36,37,35;,
  3;37,36,39;,
  3;36,38,39;,
  3;39,38,41;,
  3;38,40,41;,
  3;19,18,48;,
  3;18,49,48;,
  3;20,19,55;,
  3;19,48,55;,
  3;20,55,21;,
  3;55,54,21;,
  3;21,54,22;,
  3;54,53,22;,
  3;22,53,23;,
  3;53,52,23;,
  3;23,52,24;,
  3;52,51,24;,
  3;24,51,25;,
  3;51,50,25;,
  3;25,50,18;,
  3;50,49,18;,
  3;29,15,26;,
  3;15,8,26;,
  3;29,31,15;,
  3;31,14,15;,
  3;31,33,14;,
  3;33,13,14;,
  3;33,35,13;,
  3;35,12,13;,
  3;35,37,12;,
  3;37,11,12;,
  3;39,10,37;,
  3;10,11,37;,
  3;41,9,39;,
  3;9,10,39;,
  3;26,8,41;,
  3;8,9,41;,
  3;1,65,0;,
  3;65,66,0;,
  3;1,16,67;,
  3;16,68,67;,
  3;5,6,69;,
  3;6,70,69;,
  3;71,72,16;,
  3;72,68,16;,
  3;6,7,70;,
  3;7,73,70;,
  3;0,66,7;,
  3;66,73,7;,
  3;49,56,48;,
  3;56,63,48;,
  3;50,57,49;,
  3;57,56,49;,
  3;50,51,57;,
  3;51,58,57;,
  3;51,52,58;,
  3;52,59,58;,
  3;52,53,59;,
  3;53,60,59;,
  3;53,54,60;,
  3;54,61,60;,
  3;55,62,54;,
  3;62,61,54;,
  3;48,63,55;,
  3;63,62,55;,
  3;57,28,56;,
  3;28,27,56;,
  3;57,58,28;,
  3;58,30,28;,
  3;58,59,30;,
  3;59,32,30;,
  3;59,60,32;,
  3;60,34,32;,
  3;60,61,34;,
  3;61,36,34;,
  3;62,38,61;,
  3;38,36,61;,
  3;63,40,62;,
  3;40,38,62;,
  3;56,27,63;,
  3;27,40,63;;
 }
 MeshTextureCoords {
  64;
  0.454509;0.654784;,
  0.460574;0.665876;,
  0.460627;0.650965;,
  0.436605;0.651388;,
  0.451079;0.657250;,
  0.444350;0.646550;,
  0.433398;0.653395;,
  0.436605;0.651388;,
  0.444350;0.646550;,
  0.460627;0.650965;,
  0.454509;0.654783;,
  0.463676;0.649066;,
  0.378215;0.533647;,
  0.372303;0.538672;,
  0.373293;0.539167;,
  0.368433;0.544689;,
  0.366439;0.546980;,
  0.368433;0.544689;,
  0.373293;0.539167;,
  0.378215;0.533647;,
  0.380270;0.531360;,
  0.452098;0.641717;,
  0.439918;0.639445;,
  0.448170;0.634293;,
  0.431668;0.644599;,
  0.428251;0.646732;,
  0.431668;0.644599;,
  0.439918;0.639445;,
  0.452098;0.641717;,
  0.448170;0.634293;,
  0.455311;0.639721;,
  0.451594;0.632170;,
  0.411693;0.565114;,
  0.386230;0.535341;,
  0.397783;0.573816;,
  0.377609;0.544714;,
  0.389801;0.531458;,
  0.417455;0.561508;,
  0.411693;0.565114;,
  0.386230;0.535341;,
  0.397783;0.573816;,
  0.377609;0.544714;,
  0.383874;0.582518;,
  0.368989;0.554087;,
  0.378113;0.586123;,
  0.365418;0.557970;,
  0.368989;0.554087;,
  0.383874;0.582518;,
  0.431567;0.626072;,
  0.440773;0.620320;,
  0.422363;0.631825;,
  0.418551;0.634207;,
  0.422363;0.631825;,
  0.431567;0.626072;,
  0.440773;0.620320;,
  0.444591;0.617945;,
  0.433768;0.613421;,
  0.425935;0.618315;,
  0.437015;0.611399;,
  0.433768;0.613421;,
  0.425935;0.618315;,
  0.418105;0.623210;,
  0.414862;0.625237;,
  0.418105;0.623210;;
 }
}