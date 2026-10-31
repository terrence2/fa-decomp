.PHONY: image proof msvc-test

# Build context = project root so Dockerfile sees vendor/MSVC420 + docker/.
IMAGE := fa-decomp-env

image:
	docker build -f docker/Dockerfile -t $(IMAGE) .

# Phase 0 proof: compile+link hello.c with VC++ 4.2 under Wine, run it,
# verify the linker field is 4.20, and verify two links are byte-identical
# (frozen clock) once timestamp fields are patched to a fixed value.
proof: image
	@bash docker/proof.sh $(IMAGE)