/*
	Nazara Engine - Graphics module

	Copyright (C) 2014 Jérôme "Lynix" Leclercq (Lynix680@gmail.com)

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
	of the Software, and to permit persons to whom the Software is furnished to do
	so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#pragma once

#ifndef NAZARA_CONFIG_GRAPHICS_HPP
#define NAZARA_CONFIG_GRAPHICS_HPP

/// Chaque modification d'un paramètre du module nécessite une recompilation de celui-ci

// À partir de combien d'instances d'un même mesh/matériau l'instancing doit-il être utilisé ?
#define NAZARA_GRAPHICS_INSTANCING_MIN_INSTANCES_COUNT 100

// Utilise un tracker pour repérer les éventuels leaks (Ralentit l'exécution)
#define NAZARA_GRAPHICS_MEMORYLEAKTRACKER 0

// Active les tests de sécurité basés sur le code (Conseillé pour le développement)
#define NAZARA_GRAPHICS_SAFE 1

#endif // NAZARA_CONFIG_GRAPHICS_HPP
