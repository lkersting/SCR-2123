ADD_EXECUTABLE(tstFreeGasElasticSAlphaBetaFunction
  tstFreeGasElasticSAlphaBetaFunction.cpp)
TARGET_LINK_LIBRARIES(tstFreeGasElasticSAlphaBetaFunction data_gen_free_gas_sab)
ADD_TEST(FreeGasElasticSAlphaBetaFunction_test tstFreeGasElasticSAlphaBetaFunction)

ADD_EXECUTABLE(tstFreeGasElasticMarginalAlphaFunction
  tstFreeGasElasticMarginalAlphaFunction.cpp)
TARGET_LINK_LIBRARIES(tstFreeGasElasticMarginalAlphaFunction data_gen_free_gas_sab)
ADD_TEST(FreeGasElasticMarginalAlphaFunction_test tstFreeGasElasticMarginalAlphaFunction)

## ADD_EXECUTABLE(tstFreeGasElasticMarginalBetaFunction
##   tstFreeGasElasticMarginalBetaFunction.cpp)
## TARGET_LINK_LIBRARIES(tstFreeGasElasticMarginalBetaFunction data_gen_free_gas_sab)
## ADD_TEST(FreeGasElasticMarginalBetaFunction_test tstFreeGasElasticMarginalBetaFunction)