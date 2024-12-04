#include <src/data/hash.h>

String generateSHA256(const String &input)
{
    unsigned char hash[32];
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
    const size_t len = input.length();

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (const unsigned char *)input.c_str(), len);
    mbedtls_md_finish(&ctx, hash);
    mbedtls_md_free(&ctx);

    String hashHex;
    for (int i = 0; i < 32; i++)
    {
        hashHex += String(hash[i], HEX);
    }
    return hashHex;
}