/*
 * _coder_one_sided_hp_filter_kalman_info.c
 *
 * Code generation for function 'one_sided_hp_filter_kalman'
 *
 */

/* Include files */
#include "_coder_one_sided_hp_filter_kalman_info.h"

/* Function Definitions */
const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[11] = {
    "789ced5c4f8fdb44149fa0251455ad0a97aa08b5dd1bd24a99c201559cba5bbadad0ddee4243b55541ae634f36c3ce782c8fb3845bd44355a91242aa10e5c6b1"
    "1f80035f821b485cf90c7c01666267e3cc9a8cd77f122f1d4b56f2e27993df7bf37e33efd99380467b0788e3a2385f6d02d014afe7c4f906888e3763b921cecb",
    "f16bf4f90ab810cb4fc4e9302f44c330bae8d91481c9e1328a3ddb0b3bdff9080488337284dcf1951e26a88329da6609610b0b816e262e1d0bf252d0e7c73d03"
    "9214a243da3102533b5652ecb897b0e3522c3fbaf3f5ed4fe0971c051c76074e9fda1efc14f1c390f9707d63c7da0bd837c809e1fd417787b98870c83c6471ec",
    "22d7eafb96401fa2c03ab489506cd108c74d0d8e730a0e29d3c0c547a2d72cfa4d45bf39f6f6a04b50363f7ca6e84bf9517b7b7fec0a61f04160d3ebd2f91cee"
    "ac77b6d737e0171fddf8f0631b868c912e1b42440924b80ba91d12bb0b99cfe1047fcb9f8e47d28e660a8e4602c7dbf1e7e278b5ffcb9feb05f48b7effcf1b57",
    "caf9fe0f12fa8d147d9078cdd37e04ea37ce6938de52704839ee26937ed1786f2bfaed12fc3071034d8c47be7819bd687ebed4782f4d7fd9f1bea871ded3e0b8"
    "a6e090b223168fa085c5621978366961be31104b47dbbb37a028c04e293c78a6d1df57f4f7f3f8479e6b636be0dac41ca89ad3a205e2e9d78bbfff61f890a1fd",
    "089c0d3e5c57704859e103776c8286fe6d467d3bc422a2cbe0c30f1afd878afec33cfe49e5c309734a5827c08bb2f29265ebbf2ebcd8d2e07857c121658517a2"
    "d774bf579127dd55f4efe6f14b2a1f8419b1670ae449cf4d9e94adbd6edefb0acc8eb394cbad8357a337d6c077ed104d70e9f8f08e824bca229c2c1a628ab8d5",
    "47c44741c2ce1b73fa9b1cc9fe267aba3ce9bea227e5a2f3c3093b8af3e1a5590fb2b57f09e68fb70d66c75bca158cf7aac328659ee5f49173c813f84c3d61ea"
    "893af0a46ef3a26ebdb8ace091724a5d6107770e16923fed29fa7b79fcf39ff58434a3100f2efdb56bd68b32ea87458df32d0d8e0b0a0e2963ee455366281fbb",
    "2ca66ed855f477f3f843ce0b3d3c44aecf843be08c1d624e2810373f9a3ce96cc57d9ee76798f7b05856fa67eaf9d94cbc47f82737104cbc2f3fdfa92ebf9dc6"
    "fb6a0f073cece12c75c055058f9465fe24bab57a2c208cf9163b42418fb06fa32aa3589dacbb8ff058d17b9cc73f897c3076d71c7b8ae43fa39f0c2fb2b5ff0d",
    "cc1ff7a76076dca55cf5b8afce6f707c734817ef8df8b329fe95f1da5152bd813d170ddb5e38c631d4f4b7a9f4b799d78fca3a92b60fc5ac1f27f50128c69365"
    "8fef2dcdf767ad0f4ecb17a76f07a62e888e3ae89bf560fe7a90a71e105d537b582d3fcade9f8588780323e425d411265fcad8fe75e507f6ce2a3fb067f831d5",
    "af9a1fcfc0fc715e749d9db73e287a5f69d9f9a2c993961be78b7e7ea6bb9f7445c12365a59eed129bb786078826f735e59def17e29fd479604dda01c77614df"
    "77f1fddf4f0c1f6ac387538cb78e0fef2978a49cc607ec11eca1a99d55ed43ea287a9d92fd13d91139a8403c5dfd6764f657fc1ff99061dfd1980f038eac00f5",
    "e4fb4a9f3754b75f3bf24fc28e32f66b1b5e646c5f375e6c69f0987d47a78a23b3ef2863fbbaf140b73ebcafe091b2c283c9747a5c4254593f3c50f03c28cf3f"
    "b11d531715a81fce8f0e0d1f6ac38712eb69932f997c6911bca8ebef7bccff5e148a1ff3bf1719daff0ba1171c07",
    "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(data, 18104U, &nameCaptureInfo);
  return nameCaptureInfo;
}

mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * fldNames[4] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs" };

  mxArray *xInputs;
  const char * b_fldNames[4] = { "Version", "ResolvedFunctions", "EntryPoints",
    "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 4, fldNames);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, "Name", mxCreateString(
    "one_sided_hp_filter_kalman"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", mxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", mxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  xResult = emlrtCreateStructMatrix(1, 1, 4, b_fldNames);
  emlrtSetField(xResult, 0, "Version", mxCreateString("9.0.0.341360 (R2016a)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/* End of code generation (_coder_one_sided_hp_filter_kalman_info.c) */
