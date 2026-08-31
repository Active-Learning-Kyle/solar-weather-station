# Security Policy

## Supported scope

The current prototype is designed for a trusted local development network. It does not provide TLS, authentication, public-user accounts, hardened deployment or a secure offline update path.

Do not expose the FastAPI service or dashboard directly to the public internet. Measurement payloads may contain precise GNSS location.

## Reporting a vulnerability

Report a suspected vulnerability privately to the repository owner through the contact route on the owner's GitHub profile. Do not open a public Issue with credentials, precise coordinates, private endpoints or steps that would expose an active system.

Include:

- the affected commit or release;
- the component and configuration;
- steps to reproduce the problem;
- the possible impact; and
- any temporary mitigation already applied.

## Secret and data handling

- Copy `firmware/include/secrets.example.h` to the ignored `secrets.h`; never put real credentials in the example file.
- Keep databases, raw coordinate logs and restricted site records out of public commits.
- Redact coordinates with an opaque cover or reduce their precision before publishing an image.
- Rotate a credential immediately if it enters Git history. Deleting it in a later commit is not sufficient.
- Review build logs, Issues, Pull Requests and release assets as well as tracked files.

## Safety is separate from cybersecurity

A security review does not approve battery, 12 V, outdoor, fabrication or mounting safety. Use the field-readiness checklist and an authorised engineering review for physical deployment.
