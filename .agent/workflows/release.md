---
description: how to release a new version of cosmic-os
---

# Releasing cosmic-os

Follow these steps ONLY when explicitly requested by the user.

1. **Verify Code State**: Ensure all changes are committed and pushed to `main`.
2. **Consult User on Version**: Ask the user for the version number (e.g., `v0.2.0`) and the Celestial Codename (e.g., `Pulsar`).
3. **Execute Tagging**:
   ```bash
   git tag <version>-<codename>
   git push origin <version>-<codename>
   ```
4. **Monitor Release**: Direct the user to the GitHub Releases page to download the built ISO.

// turbo
**IMPORTANT**: Never trigger a release automatically. Always wait for user confirmation.
