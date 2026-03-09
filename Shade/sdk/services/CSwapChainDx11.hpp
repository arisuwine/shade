#pragma once
#include "../offsets.hpp"

class IDXGISwapChain;

class CSwapChainDx11 {
public:
	SCHEMA(IDXGISwapChain*, 0x170, m_pDXGISwapChain);
};