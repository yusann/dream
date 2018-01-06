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
 50;
 -1.57547;0.16837;0.28735;,
 -1.57458;-0.07713;0.41042;,
 -0.62123;0.27307;0.41061;,
 -0.65231;-0.10818;0.61349;,
 -1.59408;-0.33149;0.29768;,
 -0.72840;-0.52632;0.43451;,
 -1.62046;-0.42968;0.03234;,
 -0.79362;-0.69224;-0.00817;,
 -1.63827;-0.31419;-0.23017;,
 -0.80226;-0.49741;-0.44791;,
 -1.63706;-0.05268;-0.33606;,
 -0.75552;-0.06778;-0.61957;,
 -1.61681;0.18455;-0.20658;,
 -0.68989;0.29994;-0.40969;,
 -1.59119;0.29988;0.04202;,
 -0.62379;0.48690;0.00207;,
 -1.97290;-0.05406;0.24806;,
 -1.97336;0.07334;0.18420;,
 -1.98911;-0.04772;0.05438;,
 -1.98302;-0.18605;0.18956;,
 -1.99671;-0.23700;0.05187;,
 -2.00595;-0.17707;-0.08435;,
 -2.00532;-0.04137;-0.13930;,
 -1.99481;0.08173;-0.07211;,
 -1.98152;0.14157;0.05689;,
 0.43320;-0.11259;0.17430;,
 0.41517;-0.23094;0.28883;,
 0.47609;-0.33566;-0.05893;,
 0.30630;-0.44827;0.19269;,
 0.24113;-0.53553;-0.05155;,
 0.26533;-0.43224;-0.29687;,
 0.35791;-0.20853;-0.39528;,
 0.39520;-0.09772;-0.27975;,
 0.45826;0.00141;-0.05307;,
 -1.76937;0.15964;0.27736;,
 -1.76855;-0.06763;0.39129;,
 -1.78660;-0.30309;0.28692;,
 -1.81101;-0.39399;0.04130;,
 -1.82750;-0.28708;-0.20170;,
 -1.82639;-0.04499;-0.29973;,
 -1.80764;0.17462;-0.17987;,
 -1.78392;0.28137;0.05026;,
 0.10770;0.26422;-0.03362;,
 0.09503;0.09277;0.29507;,
 0.03990;0.11435;-0.36358;,
 -0.00928;-0.13561;-0.52238;,
 -0.08143;-0.46722;-0.38642;,
 -0.09140;-0.62003;-0.03812;,
 -0.02305;-0.49006;0.31097;,
 0.07205;-0.16744;0.44938;;
 
 96;
 3;0,1,2;,
 3;2,1,3;,
 3;4,5,1;,
 3;1,5,3;,
 3;6,7,4;,
 3;4,7,5;,
 3;6,8,7;,
 3;7,8,9;,
 3;8,10,9;,
 3;9,10,11;,
 3;12,13,10;,
 3;10,13,11;,
 3;12,14,13;,
 3;13,14,15;,
 3;0,2,14;,
 3;14,2,15;,
 3;16,17,18;,
 3;19,16,18;,
 3;20,19,18;,
 3;21,20,18;,
 3;22,21,18;,
 3;23,22,18;,
 3;24,23,18;,
 3;17,24,18;,
 3;25,26,27;,
 3;26,28,27;,
 3;28,29,27;,
 3;29,30,27;,
 3;30,31,27;,
 3;31,32,27;,
 3;32,33,27;,
 3;33,25,27;,
 3;34,35,0;,
 3;0,35,1;,
 3;35,36,1;,
 3;1,36,4;,
 3;36,37,4;,
 3;4,37,6;,
 3;37,38,6;,
 3;6,38,8;,
 3;38,39,8;,
 3;8,39,10;,
 3;40,12,39;,
 3;39,12,10;,
 3;40,41,12;,
 3;12,41,14;,
 3;34,0,41;,
 3;41,0,14;,
 3;15,2,42;,
 3;42,2,43;,
 3;15,42,13;,
 3;13,42,44;,
 3;13,44,11;,
 3;11,44,45;,
 3;9,11,46;,
 3;46,11,45;,
 3;7,9,47;,
 3;47,9,46;,
 3;7,47,5;,
 3;5,47,48;,
 3;3,5,49;,
 3;49,5,48;,
 3;2,3,43;,
 3;43,3,49;,
 3;17,16,34;,
 3;34,16,35;,
 3;16,19,35;,
 3;35,19,36;,
 3;19,20,36;,
 3;36,20,37;,
 3;20,21,37;,
 3;37,21,38;,
 3;21,22,38;,
 3;38,22,39;,
 3;23,40,22;,
 3;22,40,39;,
 3;23,24,40;,
 3;40,24,41;,
 3;17,34,24;,
 3;24,34,41;,
 3;42,43,33;,
 3;33,43,25;,
 3;42,33,44;,
 3;44,33,32;,
 3;44,32,45;,
 3;45,32,31;,
 3;45,31,46;,
 3;46,31,30;,
 3;46,30,47;,
 3;47,30,29;,
 3;48,47,28;,
 3;28,47,29;,
 3;49,48,26;,
 3;26,48,28;,
 3;43,49,25;,
 3;25,49,26;;
 
 MeshMaterialList {
  1;
  96;
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
  52;
  -0.855795;0.341718;0.388386;,
  -0.815796;0.124245;0.564836;,
  -0.840226;-0.283150;0.462435;,
  -0.868436;-0.479644;0.125541;,
  -0.890618;-0.379548;-0.250487;,
  -0.861922;0.067719;-0.502498;,
  -0.901729;0.364552;-0.232350;,
  -0.795904;0.599753;0.082665;,
  0.781939;0.394624;0.482539;,
  0.688908;-0.420550;0.590376;,
  0.486564;-0.788727;0.375720;,
  0.459891;-0.885553;-0.065542;,
  0.435047;-0.755578;-0.489731;,
  0.606542;-0.383039;-0.696698;,
  0.716690;0.402275;-0.569675;,
  0.811382;0.582636;-0.046856;,
  -0.995658;0.038824;0.084608;,
  0.937908;-0.335930;-0.086485;,
  -0.101190;0.691798;0.714966;,
  -0.166816;-0.025282;0.985664;,
  -0.209725;-0.786650;0.580686;,
  -0.235222;-0.967683;-0.090890;,
  -0.263119;-0.674487;-0.689809;,
  -0.264794;0.078655;-0.961092;,
  -0.165580;0.729359;-0.663791;,
  -0.159963;0.986261;0.041239;,
  0.026459;0.733463;0.679214;,
  0.052166;0.998312;0.025528;,
  -0.034503;0.766033;-0.641874;,
  -0.007909;0.073236;-0.997283;,
  -0.119438;-0.690437;-0.713464;,
  -0.169756;-0.985346;-0.016596;,
  -0.021593;-0.684493;0.728700;,
  0.059306;0.141831;0.988113;,
  -0.386810;0.635201;0.668504;,
  -0.350344;0.052856;0.935129;,
  -0.391630;-0.637724;0.663275;,
  -0.431300;-0.902007;0.019073;,
  -0.455747;-0.637845;-0.620845;,
  -0.360728;0.069440;-0.930082;,
  -0.458415;0.675379;-0.577684;,
  -0.266143;0.962677;0.049201;,
  0.423326;0.628507;0.652513;,
  0.402253;0.915520;-0.003806;,
  0.361651;0.645403;-0.672803;,
  0.288158;0.166656;-0.942969;,
  0.164908;-0.615983;-0.770306;,
  0.166587;-0.985075;-0.043312;,
  0.249002;-0.698951;0.670423;,
  0.349496;0.034838;0.936290;,
  0.364618;0.610431;-0.703155;,
  0.428548;0.593770;0.681017;;
  96;
  3;18,19,26;,
  3;26,19,33;,
  3;20,32,19;,
  3;19,32,33;,
  3;21,31,20;,
  3;20,31,32;,
  3;21,22,31;,
  3;31,22,30;,
  3;22,23,30;,
  3;30,23,29;,
  3;24,28,23;,
  3;23,28,29;,
  3;24,25,28;,
  3;28,25,27;,
  3;18,26,25;,
  3;25,26,27;,
  3;1,0,16;,
  3;2,1,16;,
  3;3,2,16;,
  3;4,3,16;,
  3;5,4,16;,
  3;6,5,16;,
  3;7,6,16;,
  3;0,7,16;,
  3;8,9,17;,
  3;9,10,17;,
  3;10,11,17;,
  3;11,12,17;,
  3;12,13,17;,
  3;13,14,17;,
  3;14,15,17;,
  3;15,8,17;,
  3;34,35,18;,
  3;18,35,19;,
  3;35,36,19;,
  3;19,36,20;,
  3;36,37,20;,
  3;20,37,21;,
  3;37,38,21;,
  3;21,38,22;,
  3;38,39,22;,
  3;22,39,23;,
  3;40,24,39;,
  3;39,24,23;,
  3;40,41,24;,
  3;24,41,25;,
  3;34,18,41;,
  3;41,18,25;,
  3;27,26,43;,
  3;43,26,42;,
  3;27,43,28;,
  3;28,43,44;,
  3;28,44,29;,
  3;29,44,45;,
  3;30,29,46;,
  3;46,29,45;,
  3;31,30,47;,
  3;47,30,46;,
  3;31,47,32;,
  3;32,47,48;,
  3;33,32,49;,
  3;49,32,48;,
  3;26,33,42;,
  3;42,33,49;,
  3;0,1,34;,
  3;34,1,35;,
  3;1,2,35;,
  3;35,2,36;,
  3;2,3,36;,
  3;36,3,37;,
  3;3,4,37;,
  3;37,4,38;,
  3;4,5,38;,
  3;38,5,39;,
  3;6,40,5;,
  3;5,40,39;,
  3;6,7,40;,
  3;40,7,41;,
  3;0,34,7;,
  3;7,34,41;,
  3;43,42,15;,
  3;15,42,8;,
  3;43,15,44;,
  3;44,15,14;,
  3;44,14,45;,
  3;45,14,50;,
  3;45,13,46;,
  3;46,13,12;,
  3;46,12,47;,
  3;47,12,11;,
  3;48,47,10;,
  3;10,47,11;,
  3;49,48,9;,
  3;9,48,10;,
  3;42,49,8;,
  3;8,49,51;;
 }
 MeshTextureCoords {
  50;
  0.376441;0.526155;,
  0.367662;0.530817;,
  0.362584;0.486712;,
  0.349598;0.495272;,
  0.358280;0.535798;,
  0.335027;0.505228;,
  0.354393;0.537861;,
  0.328868;0.509551;,
  0.358280;0.535798;,
  0.335027;0.505228;,
  0.367662;0.530817;,
  0.349598;0.495272;,
  0.376441;0.526155;,
  0.362584;0.486712;,
  0.380930;0.523772;,
  0.369421;0.481896;,
  0.375612;0.545792;,
  0.380168;0.543373;,
  0.375612;0.545792;,
  0.370744;0.548376;,
  0.368727;0.549447;,
  0.370744;0.548376;,
  0.375612;0.545792;,
  0.380168;0.543373;,
  0.382498;0.542136;,
  0.327630;0.451005;,
  0.323902;0.454137;,
  0.317888;0.452620;,
  0.317634;0.462058;,
  0.314948;0.465527;,
  0.317634;0.462058;,
  0.323902;0.454137;,
  0.327630;0.451005;,
  0.330747;0.447361;,
  0.379764;0.533989;,
  0.371637;0.538304;,
  0.362952;0.542915;,
  0.359354;0.544825;,
  0.362952;0.542915;,
  0.371637;0.538304;,
  0.379764;0.533989;,
  0.383920;0.531783;,
  0.347195;0.456680;,
  0.341996;0.461130;,
  0.341996;0.461130;,
  0.333211;0.467086;,
  0.322657;0.476214;,
  0.318153;0.480279;,
  0.322657;0.476214;,
  0.333211;0.467086;;
 }
}
