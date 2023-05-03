#include "stdafx.h"

FiberPool g_fiberPool;

void FiberPool::Init() {
	static function<void(void)> job1;
	static function<void(void)> job2;
	static function<void(void)> job3;
	static function<void(void)> job4;
	GetFiberManager()->AddFiber("FP1", [] {PROFILER_START(FiberPool1) GetFiberPool()->Update(job1); PROFILER_END(FiberPool1)}); //FiberPool
	GetFiberManager()->AddFiber("FP2", [] {PROFILER_START(FiberPool2) GetFiberPool()->Update(job2); PROFILER_END(FiberPool2)}); //FiberPool
	GetFiberManager()->AddFiber("FP3", [] {PROFILER_START(FiberPool3) GetFiberPool()->Update(job3); PROFILER_END(FiberPool3)}); //FiberPool
	GetFiberManager()->AddFiber("FP4", [] {PROFILER_START(FiberPool4) GetFiberPool()->Update(job4); PROFILER_END(FiberPool4)}); //FiberPool
}

void FiberPool::Update(function<void(void)>& func) {
	if (m_jobs.empty())return;
	func = std::move(m_jobs.front());
	m_jobs.pop();
	func();
}

void FiberPool::DoJob(function <void(void)> func) {
	m_jobs.emplace(move(func));
}

FiberPool* GetFiberPool() { return &g_fiberPool; }