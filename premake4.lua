solution "Wrath"
	location "build"
	includedirs { "src" }
	configurations { "Debug", "Release" }
	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }
	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
	configuration "gmake"
		buildoptions "-std=c++0x"

	newoption
	{
		trigger = "use-black-mask",
		description = "Use black as a transparency mask. Otherwise, we'll use magenta."
	}

	configuration "use-black-mask"
			defines "_ALLOW_BLACK_MASK"

	-- Our plugin library
	project "pluma"
		kind "StaticLib"
		language "C++"
		files { "src/pluma-src/*.cpp" }
		links { "dl" }
		configuration "gmake"
			buildoptions "-fPIC"

	-- Put all the stuff in this folder
	project "WrathLib"
		kind "SharedLib"
		language "C++"
		files { "src/lib/**.cpp", "src/lib/**.h" }
		links { "sfml-system", "sfml-window", "sfml-graphics", "falcon_engine", "pluma", "thor" }

	-- The actual application
	project "Wrath"
		kind "ConsoleApp"
		language "C++"
		files { "src/app/**.cpp", "src/app/**.h" }
		links { "WrathLib", "pluma" }