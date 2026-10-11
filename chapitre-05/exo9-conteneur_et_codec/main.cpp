#include <iostream>
#include <string>
#include <vector>

static int valeurHex(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return c - 'A' + 10;
}

static std::vector<int> decoder(const std::string &s) {
    std::vector<int> octets;
    if (s == "-") return octets;
    for (size_t i = 0; i + 1 < s.size(); i += 2)
        octets.push_back(valeurHex(s[i]) * 16 + valeurHex(s[i + 1]));
    return octets;
}

static bool commence(const std::vector<int> &b, size_t debut, const std::vector<int> &motif) {
    if (b.size() < debut + motif.size()) return false;
    for (size_t k = 0; k < motif.size(); k++)
        if (b[debut + k] != motif[k]) return false;
    return true;
}

static std::string conteneur(const std::vector<int> &b) {
    size_t n = b.size();
    if (n >= 12 && commence(b, 4, {0x66, 0x74, 0x79, 0x70})) return "MP4";
    if (n >= 4 && commence(b, 0, {0x1A, 0x45, 0xDF, 0xA3})) return "WEBM";
    if (n >= 12 && commence(b, 0, {0x52, 0x49, 0x46, 0x46}) &&
        commence(b, 8, {0x57, 0x41, 0x56, 0x45})) return "WAV";
    if (n >= 4 && commence(b, 0, {0x4F, 0x67, 0x67, 0x53})) return "OGG";
    if (n >= 4 && commence(b, 0, {0x66, 0x4C, 0x61, 0x43})) return "FLAC";
    if (n >= 3 && commence(b, 0, {0x49, 0x44, 0x33})) return "MP3";
    if (n >= 2 && b[0] == 0xFF && b[1] >= 0xE0) return "MP3";
    return "INCONNU";
}

static std::string nommerCodec(const std::string &code) {
    if (code == "mp4a") return "aac";
    if (code == "Opus" || code == "opus") return "opus";
    if (code == "avc1" || code == "avc3") return "h264";
    if (code == "hvc1" || code == "hev1") return "h265";
    if (code == "vp08") return "vp8";
    if (code == "vp09") return "vp9";
    if (code == "mp4v") return "mpeg4";
    if (code == ".mp3") return "mp3";
    if (code == "twos" || code == "sowt" || code == "lpcm") return "pcm";
    return code;
}

static bool lisible(const std::string &code) {
    return code == "mjpa" || code == "jpeg" || code == "MJPG" || code == "avc1" ||
           code == "avc3" || code == "hvc1" || code == "hev1" || code == "av01";
}

int main() {
    int n = 0;
    std::cin >> n;
    int mp4 = 0, lisibles = 0, inconnus = 0;

    for (int i = 0; i < n; i++) {
        std::string nom, hex;
        int p = 0;
        std::cin >> nom >> hex >> p;

        // on lit toujours toutes les pistes, meme si on les ignore ensuite
        std::vector<std::string> types(p), codes(p);
        for (int k = 0; k < p; k++) std::cin >> types[k] >> codes[k];

        std::string c = conteneur(decoder(hex));
        std::cout << nom << " " << c << "\n";

        if (c == "INCONNU") inconnus++;
        if (c != "MP4") continue;
        mp4++;

        std::string premiereVideo;
        bool aVideo = false;
        for (int k = 0; k < p; k++) {
            bool video = (types[k] == "vide");
            std::cout << nom << " PISTE " << (k + 1) << " " << (video ? "VIDEO" : "AUDIO")
                      << " " << nommerCodec(codes[k]) << "\n";
            if (video && !aVideo) {
                aVideo = true;
                premiereVideo = codes[k];
            }
        }

        std::string verdict = "SANS_IMAGE";
        if (aVideo) verdict = lisible(premiereVideo) ? "LISIBLE" : "ECHEC";
        if (verdict == "LISIBLE") lisibles++;
        std::cout << nom << " LECTEUR " << verdict << "\n";
    }

    std::cout << "MP4 " << mp4 << "\n";
    std::cout << "LISIBLES " << lisibles << "\n";
    std::cout << "INCONNUS " << inconnus << "\n";
    return 0;
}
