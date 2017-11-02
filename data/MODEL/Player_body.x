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
 86;
 0.05827;2.18258;0.00000;,
 0.54535;2.14218;-0.48708;,
 0.05827;2.14218;-0.68883;,
 0.05827;2.18258;0.00000;,
 0.74710;2.14218;0.00000;,
 0.05827;2.18258;0.00000;,
 0.54535;2.06972;0.48708;,
 0.05827;2.18258;0.00000;,
 0.05827;2.06972;0.68883;,
 0.05827;-0.97847;-0.68883;,
 0.54535;-0.97847;-0.48708;,
 0.05827;-1.09133;-0.00000;,
 0.80749;-0.97847;-0.00000;,
 0.05827;-1.09133;-0.00000;,
 0.54535;-0.97847;0.48708;,
 0.05827;-1.09133;-0.00000;,
 0.05827;-0.97847;0.68883;,
 0.05827;-1.09133;-0.00000;,
 0.95827;1.92107;-0.90000;,
 0.05827;1.99354;-1.27279;,
 1.30691;1.83653;0.00000;,
 0.95827;1.81237;0.76715;,
 0.05827;1.76890;1.08197;,
 1.16172;1.38542;-1.17591;,
 0.05827;1.38542;-1.66298;,
 1.38309;1.38542;0.00000;,
 1.16172;1.37334;1.06721;,
 0.05827;1.37334;1.41902;,
 1.25860;0.57581;-1.27279;,
 0.05827;0.57581;-1.80000;,
 1.70127;0.57581;0.00000;,
 1.25860;0.57581;1.27279;,
 0.05827;0.57581;1.68406;,
 1.18587;-0.00432;-1.17591;,
 0.05827;-0.00432;-1.66298;,
 1.67295;-0.00432;-0.00000;,
 1.18587;-0.00432;1.26045;,
 0.05827;-0.00432;1.78375;,
 0.90996;-0.47959;-0.90000;,
 0.05827;-0.55205;-1.27279;,
 1.14991;-0.49166;-0.00000;,
 0.90996;-0.47959;1.02077;,
 0.05827;-0.55205;1.39357;,
 -0.05827;2.14218;-0.68883;,
 -0.54535;2.14218;-0.48708;,
 -0.05827;2.18258;0.00000;,
 -0.74710;2.14218;0.00000;,
 -0.05827;2.18258;0.00000;,
 -0.54535;2.06972;0.48708;,
 -0.05827;2.18258;0.00000;,
 -0.05827;2.06972;0.68883;,
 -0.05827;2.18258;0.00000;,
 -0.05827;-1.09133;0.00000;,
 -0.54535;-0.97847;-0.48708;,
 -0.05827;-0.97847;-0.68883;,
 -0.05827;-1.09133;0.00000;,
 -0.80749;-0.97847;0.00000;,
 -0.05827;-1.09133;0.00000;,
 -0.54535;-0.97847;0.48708;,
 -0.05827;-1.09133;0.00000;,
 -0.05827;-0.97847;0.68883;,
 -0.95827;1.92107;-0.90000;,
 -0.05827;1.99354;-1.27279;,
 -1.30691;1.83653;0.00000;,
 -0.95827;1.81237;0.76715;,
 -0.05827;1.76890;1.08197;,
 -0.05827;1.38542;-1.66298;,
 -1.16172;1.38542;-1.17591;,
 -1.38309;1.38542;0.00000;,
 -1.16172;1.37334;1.06721;,
 -0.05827;1.37334;1.41902;,
 -1.25860;0.57581;-1.27279;,
 -0.05827;0.57581;-1.80000;,
 -1.70127;0.57581;0.00000;,
 -1.25860;0.57581;1.27279;,
 -0.05827;0.57581;1.68406;,
 -0.05827;-0.00432;-1.66298;,
 -1.18587;-0.00432;-1.17591;,
 -1.67295;-0.00432;0.00000;,
 -1.18587;-0.00432;1.26045;,
 -0.05827;-0.00432;1.78375;,
 -0.90996;-0.47959;-0.90000;,
 -0.05827;-0.55205;-1.27279;,
 -1.14991;-0.49166;0.00000;,
 -0.90996;-0.47959;1.02077;,
 -0.05827;-0.55205;1.39357;;
 
 128;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,11;,
 3;10,12,13;,
 3;12,14,15;,
 3;14,16,17;,
 3;2,1,18;,
 3;2,18,19;,
 3;1,4,20;,
 3;1,20,18;,
 3;4,6,21;,
 3;4,21,20;,
 3;6,8,22;,
 3;6,22,21;,
 3;18,23,24;,
 3;18,24,19;,
 3;18,20,25;,
 3;18,25,23;,
 3;21,26,25;,
 3;21,25,20;,
 3;22,27,26;,
 3;22,26,21;,
 3;24,23,28;,
 3;24,28,29;,
 3;25,30,28;,
 3;25,28,23;,
 3;26,31,30;,
 3;26,30,25;,
 3;27,32,31;,
 3;27,31,26;,
 3;28,33,34;,
 3;28,34,29;,
 3;30,35,33;,
 3;30,33,28;,
 3;31,36,35;,
 3;31,35,30;,
 3;32,37,36;,
 3;32,36,31;,
 3;34,33,38;,
 3;34,38,39;,
 3;35,40,38;,
 3;35,38,33;,
 3;35,36,41;,
 3;35,41,40;,
 3;37,42,41;,
 3;37,41,36;,
 3;38,10,9;,
 3;38,9,39;,
 3;40,12,10;,
 3;40,10,38;,
 3;40,41,14;,
 3;40,14,12;,
 3;41,42,16;,
 3;41,16,14;,
 3;43,44,45;,
 3;44,46,47;,
 3;46,48,49;,
 3;48,50,51;,
 3;52,53,54;,
 3;55,56,53;,
 3;57,58,56;,
 3;59,60,58;,
 3;61,44,43;,
 3;62,61,43;,
 3;63,46,44;,
 3;61,63,44;,
 3;64,48,46;,
 3;63,64,46;,
 3;65,50,48;,
 3;64,65,48;,
 3;66,67,61;,
 3;62,66,61;,
 3;68,63,61;,
 3;67,68,61;,
 3;68,69,64;,
 3;63,68,64;,
 3;69,70,65;,
 3;64,69,65;,
 3;71,67,66;,
 3;72,71,66;,
 3;71,73,68;,
 3;67,71,68;,
 3;73,74,69;,
 3;68,73,69;,
 3;74,75,70;,
 3;69,74,70;,
 3;76,77,71;,
 3;72,76,71;,
 3;77,78,73;,
 3;71,77,73;,
 3;78,79,74;,
 3;73,78,74;,
 3;79,80,75;,
 3;74,79,75;,
 3;81,77,76;,
 3;82,81,76;,
 3;81,83,78;,
 3;77,81,78;,
 3;84,79,78;,
 3;83,84,78;,
 3;84,85,80;,
 3;79,84,80;,
 3;54,53,81;,
 3;82,54,81;,
 3;53,56,83;,
 3;81,53,83;,
 3;58,84,83;,
 3;56,58,83;,
 3;60,85,84;,
 3;58,60,84;,
 4;2,43,45,0;,
 4;7,51,50,8;,
 4;11,52,54,9;,
 4;16,60,59,17;,
 4;19,62,43,2;,
 4;8,50,65,22;,
 4;24,66,62,19;,
 4;22,65,70,27;,
 4;29,72,66,24;,
 4;27,70,75,32;,
 4;34,76,72,29;,
 4;32,75,80,37;,
 4;39,82,76,34;,
 4;37,80,85,42;,
 4;9,54,82,39;,
 4;42,85,60,16;;
 
 MeshMaterialList {
  2;
  128;
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
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.412000;0.400000;0.467000;1.000000;;
   8.000000;
   0.000000;0.000000;0.000000;;
   0.111240;0.108000;0.126090;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  74;
  0.034760;0.997652;0.059015;,
  0.070041;0.978636;-0.193302;,
  0.227878;0.962960;-0.144151;,
  0.293362;0.950975;0.097901;,
  0.180917;0.915829;0.358506;,
  0.080523;0.915724;0.393656;,
  0.147289;0.805327;-0.574242;,
  0.532170;0.718813;-0.447328;,
  0.734538;0.678510;0.008868;,
  0.544392;0.711657;0.444051;,
  0.145469;0.724690;0.673545;,
  0.260012;0.354170;-0.898308;,
  0.737737;0.353580;-0.575088;,
  0.949025;0.313526;-0.032454;,
  0.648260;0.487880;0.584578;,
  0.172303;0.445689;0.878449;,
  0.205686;-0.031544;-0.978110;,
  0.702612;0.034482;-0.710737;,
  0.992874;0.115177;-0.030596;,
  0.698686;0.100838;0.708287;,
  0.215187;0.180165;0.959810;,
  0.254747;-0.408963;-0.876272;,
  0.728100;-0.359405;-0.583693;,
  0.891556;-0.450899;0.042647;,
  0.625991;-0.269550;0.731764;,
  0.249510;-0.300507;0.920565;,
  0.176614;-0.692595;-0.699371;,
  0.507611;-0.696637;-0.506979;,
  0.739071;-0.673578;-0.008132;,
  0.509038;-0.712673;0.482677;,
  0.171666;-0.723301;0.668855;,
  0.133613;-0.888252;-0.439495;,
  0.420873;-0.848035;-0.322028;,
  0.510200;-0.860056;-0.000000;,
  0.411021;-0.860668;0.300520;,
  0.121488;-0.911638;0.392628;,
  0.072617;-0.997360;-0.000000;,
  -0.034760;0.997652;0.059015;,
  -0.070041;0.978636;-0.193302;,
  -0.227878;0.962960;-0.144151;,
  -0.293362;0.950975;0.097901;,
  -0.180917;0.915829;0.358506;,
  -0.080523;0.915724;0.393656;,
  -0.147289;0.805327;-0.574242;,
  -0.532170;0.718813;-0.447328;,
  -0.734538;0.678510;0.008868;,
  -0.544392;0.711657;0.444051;,
  -0.145469;0.724690;0.673545;,
  -0.260012;0.354170;-0.898308;,
  -0.737737;0.353580;-0.575088;,
  -0.949025;0.313526;-0.032454;,
  -0.648260;0.487880;0.584578;,
  -0.172303;0.445689;0.878449;,
  -0.205686;-0.031544;-0.978110;,
  -0.702612;0.034482;-0.710737;,
  -0.992874;0.115177;-0.030596;,
  -0.698686;0.100838;0.708287;,
  -0.215187;0.180165;0.959810;,
  -0.254747;-0.408963;-0.876272;,
  -0.728100;-0.359405;-0.583693;,
  -0.891556;-0.450899;0.042647;,
  -0.625991;-0.269550;0.731764;,
  -0.249510;-0.300507;0.920565;,
  -0.176614;-0.692595;-0.699371;,
  -0.507611;-0.696637;-0.506979;,
  -0.739071;-0.673578;-0.008132;,
  -0.509038;-0.712673;0.482677;,
  -0.171666;-0.723301;0.668855;,
  -0.133613;-0.888252;-0.439495;,
  -0.420873;-0.848035;-0.322028;,
  -0.510200;-0.860056;0.000000;,
  -0.411021;-0.860668;0.300520;,
  -0.121488;-0.911638;0.392628;,
  -0.072617;-0.997360;0.000000;;
  128;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;31,32,36;,
  3;32,33,36;,
  3;33,34,36;,
  3;34,35,36;,
  3;1,2,7;,
  3;1,7,6;,
  3;2,3,8;,
  3;2,8,7;,
  3;3,4,9;,
  3;3,9,8;,
  3;4,5,10;,
  3;4,10,9;,
  3;7,12,11;,
  3;7,11,6;,
  3;7,8,13;,
  3;7,13,12;,
  3;9,14,13;,
  3;9,13,8;,
  3;10,15,14;,
  3;10,14,9;,
  3;11,12,17;,
  3;11,17,16;,
  3;13,18,17;,
  3;13,17,12;,
  3;14,19,18;,
  3;14,18,13;,
  3;15,20,19;,
  3;15,19,14;,
  3;17,22,21;,
  3;17,21,16;,
  3;18,23,22;,
  3;18,22,17;,
  3;19,24,23;,
  3;19,23,18;,
  3;20,25,24;,
  3;20,24,19;,
  3;21,22,27;,
  3;21,27,26;,
  3;23,28,27;,
  3;23,27,22;,
  3;23,24,29;,
  3;23,29,28;,
  3;25,30,29;,
  3;25,29,24;,
  3;27,32,31;,
  3;27,31,26;,
  3;28,33,32;,
  3;28,32,27;,
  3;28,29,34;,
  3;28,34,33;,
  3;29,30,35;,
  3;29,35,34;,
  3;38,39,37;,
  3;39,40,37;,
  3;40,41,37;,
  3;41,42,37;,
  3;73,69,68;,
  3;73,70,69;,
  3;73,71,70;,
  3;73,72,71;,
  3;44,39,38;,
  3;43,44,38;,
  3;45,40,39;,
  3;44,45,39;,
  3;46,41,40;,
  3;45,46,40;,
  3;47,42,41;,
  3;46,47,41;,
  3;48,49,44;,
  3;43,48,44;,
  3;50,45,44;,
  3;49,50,44;,
  3;50,51,46;,
  3;45,50,46;,
  3;51,52,47;,
  3;46,51,47;,
  3;54,49,48;,
  3;53,54,48;,
  3;54,55,50;,
  3;49,54,50;,
  3;55,56,51;,
  3;50,55,51;,
  3;56,57,52;,
  3;51,56,52;,
  3;58,59,54;,
  3;53,58,54;,
  3;59,60,55;,
  3;54,59,55;,
  3;60,61,56;,
  3;55,60,56;,
  3;61,62,57;,
  3;56,61,57;,
  3;64,59,58;,
  3;63,64,58;,
  3;64,65,60;,
  3;59,64,60;,
  3;66,61,60;,
  3;65,66,60;,
  3;66,67,62;,
  3;61,66,62;,
  3;68,69,64;,
  3;63,68,64;,
  3;69,70,65;,
  3;64,69,65;,
  3;71,66,65;,
  3;70,71,65;,
  3;72,67,66;,
  3;71,72,66;,
  4;1,38,37,0;,
  4;0,37,42,5;,
  4;36,73,68,31;,
  4;35,72,73,36;,
  4;6,43,38,1;,
  4;5,42,47,10;,
  4;11,48,43,6;,
  4;10,47,52,15;,
  4;16,53,48,11;,
  4;15,52,57,20;,
  4;21,58,53,16;,
  4;20,57,62,25;,
  4;26,63,58,21;,
  4;25,62,67,30;,
  4;31,68,63,26;,
  4;30,67,72,35;;
 }
 MeshTextureCoords {
  86;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.062500;1.000000;,
  0.250000;0.875000;,
  0.187500;1.000000;,
  0.375000;0.875000;,
  0.312500;1.000000;,
  0.500000;0.875000;,
  0.437500;1.000000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.062500;0.000000;,
  0.250000;0.125000;,
  0.187500;0.000000;,
  0.375000;0.125000;,
  0.312500;0.000000;,
  0.500000;0.125000;,
  0.437500;0.000000;,
  0.062500;1.000000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.187500;1.000000;,
  0.250000;0.875000;,
  0.312500;1.000000;,
  0.375000;0.875000;,
  0.437500;1.000000;,
  0.500000;0.875000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;;
 }
}
