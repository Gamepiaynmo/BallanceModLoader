#pragma once

#ifndef BML_EXPORT
#ifdef BML_EXPORTS
#define BML_EXPORT __declspec(dllexport)
#else
#define BML_EXPORT __declspec(dllimport)
#endif
#endif
