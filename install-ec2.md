# STEP 1: Launch Your EC2 Instance

## Access EC2 Dashboard
On the EC2 Dashboard:
1. Click **"Launch Instance"** (orange button)
2. Name your instance: e.g., `my-cuda-instance`

## Choose AMI (Amazon Machine Image)
- Select **"Ubuntu"** from Quick Start
- Choose **Ubuntu Server 22.04 LTS** or **24.04 LTS** (64-bit x86)
- ⚠️ **DO NOT** select Deep Learning AMI - choose plain Ubuntu

## Choose Instance Type
1. Click dropdown and filter by GPU instances
2. Select a GPU instance like:
    - `g4dn.xlarge` (cheapest, good for learning) - ~$0.52/hr
    - `g5.xlarge` (newer, faster) - ~$1.00/hr
    - `p3.2xlarge` (powerful) - ~$3.06/hr

## Configure Key Pair
- **If you have one:** Select it
- **If not:** Click "Create new key pair"
  - Name: `my-cuda-key`
  - Type: RSA
  - Format: `.pem` (for Linux/Mac) or `.ppk` (for PuTTY on Windows)
  - Download and save it - you'll need this to connect!

## Network Settings
- Keep default VPC
- Enable "Auto-assign public IP"
- Security group: Allow SSH (port 22) from your IP

## Configure Storage
- Change from 8 GB to at least **30 GB** (recommend **50 GB**)
- Keep gp3 (SSD)

## Advanced Details (Optional but recommended)
- Scroll down to "User data" section
- You can paste the installation script here to auto-install on first boot

## Launch
Click **"Launch Instance"**

# STEP 2: Wait for Instance to Start

1. Click **"View Instances"**
2. Wait until Instance State shows **"Running"** (takes ~1-2 minutes)
3. Note the **Public IPv4 address** (you'll need this to connect)

# STEP 3: Connect to Your Instance

## On Linux/Mac:
```bash
# Make key file secure
chmod 400 ~/Downloads/my-cuda-key.pem

# Connect via SSH (replace with YOUR instance IP)
ssh -i ~/Downloads/my-cuda-key.pem ubuntu@YOUR-INSTANCE-IP
```

## On Windows:
- Use PuTTY or Windows Terminal with the `.ppk` key
- Or use EC2 Instance Connect (browser-based) - easier option!

## Easier method:
On EC2 console, select your instance → Click **"Connect"** → Choose **"EC2 Instance Connect"** → Click **"Connect"**

# STEP 4: Install CUDA (Once Connected)

Now that you're SSH'd into your instance, run these commands:

## Method A: Manual Installation (Full Control)

### Update System
```bash
# Update system
sudo apt update && sudo apt upgrade -y
sudo apt install -y dkms linux-headers-aws linux-modules-extra-aws gcc make pkg-config
```

### Add NVIDIA Repository
```bash
# Add NVIDIA repository
cd /tmp
DISTRO=$(. /etc/os-release;echo $ID$VERSION_ID | sed -e 's/\.//g')
ARCH=$([ "$(uname -m)" = "x86_64" ] && echo "x86_64" || echo "sbsa")
curl -L -O https://developer.download.nvidia.com/compute/cuda/repos/$DISTRO/$ARCH/cuda-keyring_1.1-1_all.deb
sudo apt install -y ./cuda-keyring_1.1-1_all.deb
sudo apt update
```

### Install NVIDIA Driver
```bash
# Install NVIDIA driver
sudo apt install -y nvidia-driver-550 nvidia-utils-550

# Reboot (REQUIRED!)
sudo reboot
```

**Wait 1-2 minutes, then reconnect via SSH**

### Verify Driver Installation
```bash
# Verify driver installation
nvidia-smi
```
You should see your GPU info! ✅

### Install CUDA Toolkit
```bash
# Install CUDA Toolkit
sudo apt install -y cuda-toolkit-12

# Set environment variables
echo 'export PATH=/usr/local/cuda/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda/lib64:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc

# Verify CUDA
nvcc --version
```

**Done! 🎉**