#pragma once
#include <memory>
#include "Scene.h"
#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"
#include "Material.h"
#include "DummyBRDF.h"
#include "DiffuseBRDF.h"
/// This is just an incapsulation of the creation of a scene object.
class SceneBuilder {
public:
	static void build_cornell_box(Scene &scene) {
		//Create the BRDFs
		std::shared_ptr<DummyBRDF> dummy_brdf = std::make_shared<DummyBRDF>();
		std::shared_ptr<DiffuseBRDF> diffuse_brdf = std::make_shared<DiffuseBRDF>();
		std::shared_ptr<DiffuseBRDF> second_diffuse_brdf = std::make_shared<DiffuseBRDF>();
		second_diffuse_brdf->set_absorption(0.0f);

		//Add light sources to both vectors, easier to compare if light was intersected
		std::shared_ptr<Plane> area_light1 = std::make_shared<Plane>(glm::vec3(5.0f, 14.99f, 5.0), std::make_shared<Material>(glm::vec3(1), glm::vec3(1), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light2 = std::make_shared<Plane>(glm::vec3(-5.0f, 14.99f, 5.0), std::make_shared<Material>(glm::vec3(0.1f,0.1f,0.5f), glm::vec3(1), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light3 = std::make_shared<Plane>(glm::vec3(5.0f, 14.99f, -5.0), std::make_shared<Material>(glm::vec3(0.1f, 0.1f, 0.5f), glm::vec3(1), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light4 = std::make_shared<Plane>(glm::vec3(-5.0f, 14.99f, -5.0), std::make_shared<Material>(glm::vec3(0.1f, 0.1f, 0.5f), glm::vec3(1), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		scene.add_primitive(area_light1);
		scene.add_light_source(area_light1);
		scene.add_primitive(area_light2);
		scene.add_light_source(area_light2);
		
		scene.add_primitive(area_light3);
		scene.add_light_source(area_light3);
		scene.add_primitive(area_light4);
		scene.add_light_source(area_light4);

		//Add surfaces
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 0, 0), std::make_shared<Material>(glm::vec3(0.5), glm::vec3(0), diffuse_brdf), 5.0f)); //Implicit surface
		//scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 10, 0), nullptr, 1.0f)); //Implicit surface
		//scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 10, 0), nullptr, 1.0f)); //Implicit surface

		//Add walls
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 15, 0), std::make_shared<Material>(glm::vec3(0.5, 0.0001, 0.0001), glm::vec3(0), second_diffuse_brdf), glm::vec3(0, -1, 0))); //Ceiling plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, -15, 0), std::make_shared<Material>(glm::vec3(0.0001, 0.5, 0.0001), glm::vec3(0), diffuse_brdf), glm::vec3(0, 1, 0))); //Floor plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(-15, 0, 0), std::make_shared<Material>(glm::vec3(0.5, 0.5, 0.0001), glm::vec3(0), diffuse_brdf), glm::vec3(1, 0, 0))); //Left plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(15, 0, 0), std::make_shared<Material>(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0), diffuse_brdf), glm::vec3(-1, 0, 0))); //Right plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 0, 15), std::make_shared<Material>(glm::vec3(0.0001, 0.0001, 0.5), glm::vec3(0), diffuse_brdf), glm::vec3(0, 0, -1))); //Back plane
	}
};