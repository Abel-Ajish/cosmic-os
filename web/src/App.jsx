import { useState, useEffect, useRef } from 'react';
import './App.css';

function App() {
  const [scrolled, setScrolled] = useState(false);
  const [mobileMenuOpen, setMobileMenuOpen] = useState(false);

  /* Parallax Refs */
  const starsRef = useRef(null);
  const moonRef = useRef(null);
  const mountainsBehindRef = useRef(null);
  const mountainsFrontRef = useRef(null);
  const titleRef = useRef(null);
  const btnRef = useRef(null);
  const headerRef = useRef(null);

  const toggleMobileMenu = () => {
    setMobileMenuOpen(!mobileMenuOpen);
  };

  const closeMobileMenu = () => {
    setMobileMenuOpen(false);
  };

  useEffect(() => {
    const handleScroll = () => {
      const value = window.scrollY;

      if (window.innerWidth > 768) { // Only parallax on desktop for performance
        if (starsRef.current) starsRef.current.style.left = value * 0.25 + 'px';
        if (moonRef.current) moonRef.current.style.top = value * 1.05 + 'px';
        if (mountainsBehindRef.current) mountainsBehindRef.current.style.top = value * 0.5 + 'px';
        if (mountainsFrontRef.current) mountainsFrontRef.current.style.top = value * 0 + 'px';
        if (titleRef.current) {
          titleRef.current.style.marginRight = value * 4 + 'px';
          titleRef.current.style.marginTop = value * 1.5 + 'px';
        }
        if (btnRef.current) btnRef.current.style.marginTop = value * 1.5 + 'px';
      }

      setScrolled(value > 50);
    };

    window.addEventListener('scroll', handleScroll);
    return () => window.removeEventListener('scroll', handleScroll);
  }, []);

  const scrollToSection = (id) => {
    const element = document.getElementById(id);
    if (element) {
      element.scrollIntoView({ behavior: 'smooth' });
      closeMobileMenu();
    }
  };

  const features = [
    {
      icon: '🔐',
      title: 'Multi-User System',
      description: 'Secure login screen with password protection for multiple users. Built-in authentication system with cosmic-login.'
    },
    {
      icon: '🌐',
      title: 'Networking',
      description: 'Built-in cosmic-ping and kernel-level TCP/IP support. Full networking stack with cosmic-netinfo and cosmic-http.'
    },
    {
      icon: '📝',
      title: 'Advanced Editing',
      description: 'Full-featured cosmic-editor with line numbers, syntax highlighting, and file persistence.'
    },
    {
      icon: '📊',
      title: 'Real-time Monitoring',
      description: 'Visual activity bars with cosmic-pulse and cosmic-top for system resource monitoring.'
    },
    {
      icon: '🎮',
      title: 'Entertainment',
      description: 'Terminal-based games like cosmic-snake, cosmic-matrix effects, and interactive experiences.'
    },
    {
      icon: '🚀',
      title: 'Aesthetic UI',
      description: 'ANSI-powered cosmic themes, beautiful matrix effects, and formatted chronometers.'
    }
  ];

  const apps = [
    { icon: '👋', name: 'hello', description: 'Welcome message' },
    { icon: '🧮', name: 'cosmic-calc', description: 'Calculator app' },
    { icon: 'ℹ️', name: 'sysinfo', description: 'System information' },
    { icon: '⚡', name: 'powerctl', description: 'Power management' },
    { icon: '💻', name: 'cosmic-shell', description: 'Custom shell' },
    { icon: '📊', name: 'cosmic-top', description: 'Process monitor' },
    { icon: '📝', name: 'cosmic-editor', description: 'Text editor' },
    { icon: '👤', name: 'whoami', description: 'User info' },
    { icon: '🎨', name: 'cosmic-fetch', description: 'System fetch' },
    { icon: '⏱️', name: 'cosmic-uptime', description: 'System uptime' },
    { icon: '💭', name: 'cosmic-quotes', description: 'Inspirational quotes' },
    { icon: '🕐', name: 'cosmic-time', description: 'Time display' },
    { icon: '🌌', name: 'cosmic-matrix', description: 'Matrix effect' },
    { icon: '✅', name: 'cosmic-todo', description: 'Todo manager' },
    { icon: '📈', name: 'cosmic-pulse', description: 'Activity monitor' },
    { icon: '🐍', name: 'cosmic-snake', description: 'Snake game' },
    { icon: '🔐', name: 'cosmic-login', description: 'Login system' },
    { icon: '🌐', name: 'cosmic-ping', description: 'Network ping' },
    { icon: '📡', name: 'cosmic-netinfo', description: 'Network info' },
    { icon: '🌍', name: 'cosmic-http', description: 'HTTP client' }
  ];

  const stats = [
    { number: '20+', label: 'Custom Apps' },
    { number: '100%', label: 'From Scratch' },
    { number: 'Linux', label: 'Kernel Based' },
    { number: 'MIT', label: 'Open Source' }
  ];



  return (
    <div className="app">
      {/* Navbar */}
      <nav className={`navbar ${scrolled ? 'scrolled' : ''}`} ref={headerRef}>
        <div className="container">
          <div className="nav-content">
            <a href="#" className="logo">
              <span>🌌</span>
              cosmic-os
            </a>

            {/* Desktop Nav */}
            <ul className="nav-links">
              <li><a href="#features" className="nav-link" onClick={(e) => { e.preventDefault(); scrollToSection('features'); }}>Features</a></li>
              <li><a href="#apps" className="nav-link" onClick={(e) => { e.preventDefault(); scrollToSection('apps'); }}>Apps</a></li>
              <li><a href="#download" className="nav-link" onClick={(e) => { e.preventDefault(); scrollToSection('download'); }}>Download</a></li>
              <li><a href="https://github.com/Abel-Ajish/cosmic-os" target="_blank" rel="noopener noreferrer" className="nav-link">GitHub</a></li>
            </ul>

            {/* Mobile Menu Toggle */}
            <div className={`menu-toggle ${mobileMenuOpen ? 'open' : ''}`} onClick={toggleMobileMenu}>
              <span></span>
              <span></span>
              <span></span>
            </div>
          </div>

          {/* Mobile Menu Overlay */}
          <div className={`mobile-menu ${mobileMenuOpen ? 'open' : ''}`}>
            <ul className="mobile-nav-links">
              <li><a href="#features" onClick={(e) => { e.preventDefault(); scrollToSection('features'); }}>Features</a></li>
              <li><a href="#apps" onClick={(e) => { e.preventDefault(); scrollToSection('apps'); }}>Apps</a></li>
              <li><a href="#download" onClick={(e) => { e.preventDefault(); scrollToSection('download'); }}>Download</a></li>
              <li><a href="https://github.com/Abel-Ajish/cosmic-os" target="_blank" rel="noopener noreferrer">GitHub</a></li>
            </ul>
          </div>
        </div>
      </nav>

      {/* Parallax Hero Section */}
      <section className="main-container">
        <img src="/img/stars.png" id="stars" ref={starsRef} alt="stars" className="parallax-img" />
        <img src="/img/moon.png" id="moon" ref={moonRef} alt="moon" className="parallax-img" />
        <img src="/img/mountains_behind.png" id="mountains_behind" ref={mountainsBehindRef} alt="mountains behind" className="parallax-img" />

        <div className="hero-content-wrapper" ref={titleRef}>
          <h2 className="parallax-title">cosmic-os</h2>
          <p className="parallax-subtitle">Explore the Universe of Code</p>
        </div>

        <a href="#features" className="parallax-btn" id="button" ref={btnRef} onClick={(e) => { e.preventDefault(); scrollToSection('features'); }}>Explore</a>

        <img src="/img/mountains_front.png" id="mountains_front" ref={mountainsFrontRef} alt="mountains front" className="parallax-img" />
      </section>

      {/* Features Section */}
      <section id="features" className="section">
        <div className="container">
          <div className="text-center">
            <h2>Pro Edition Features</h2>
            <p style={{ maxWidth: '700px', margin: '0 auto', fontSize: '1.125rem' }}>
              Built for learning, designed for performance. Explore the powerful features that make cosmic-os unique.
            </p>
          </div>
          <div className="feature-grid">
            {features.map((feature, index) => (
              <div key={index} className="glass-card feature-card">
                <div className="feature-icon">{feature.icon}</div>
                <h3 className="feature-title">{feature.title}</h3>
                <p className="feature-description">{feature.description}</p>
              </div>
            ))}
          </div>
        </div>
      </section>

      {/* Apps Section */}
      <section id="apps" className="section">
        <div className="container">
          <div className="text-center">
            <h2>Built-in Applications</h2>
            <p style={{ maxWidth: '700px', margin: '0 auto', fontSize: '1.125rem' }}>
              20+ custom C applications designed for education and productivity. All built from scratch.
            </p>
          </div>
          <div className="apps-grid">
            {apps.map((app, index) => (
              <div key={index} className="glass-card app-card">
                <div className="app-icon">{app.icon}</div>
                <div className="app-name">{app.name}</div>
                <div className="app-description">{app.description}</div>
              </div>
            ))}
          </div>
        </div>
      </section>

      {/* Stats Section */}
      <section className="section">
        <div className="container">
          <div className="stats-grid">
            {stats.map((stat, index) => (
              <div key={index} className="glass-card stat-card">
                <span className="stat-number">{stat.number}</span>
                <span className="stat-label">{stat.label}</span>
              </div>
            ))}
          </div>
        </div>
      </section>

      {/* Download Section */}
      <section id="download" className="section">
        <div className="container">
          <div className="glass-card" style={{ maxWidth: '800px', margin: '0 auto', textAlign: 'center' }}>
            <h2>Get Started Today</h2>
            <p style={{ fontSize: '1.125rem', marginBottom: 'var(--spacing-lg)' }}>
              Download the latest cosmic-os ISO from GitHub Actions and boot it in VirtualBox or QEMU.
            </p>

            <div style={{ marginBottom: 'var(--spacing-lg)', padding: 'var(--spacing-md)', background: 'rgba(0,0,0,0.2)', borderRadius: 'var(--radius-md)' }}>
              <h3 style={{ fontSize: '1.25rem', marginBottom: 'var(--spacing-sm)' }}>🔑 Default Login Credentials</h3>
              <div style={{ display: 'grid', gridTemplateColumns: 'repeat(auto-fit, minmax(200px, 1fr))', gap: 'var(--spacing-md)', marginTop: 'var(--spacing-md)' }}>
                <div>
                  <div style={{ fontWeight: '600', color: 'var(--cosmic-primary-light)' }}>Username: cosmic</div>
                  <div style={{ color: 'var(--text-secondary)' }}>Password: space</div>
                </div>
                <div>
                  <div style={{ fontWeight: '600', color: 'var(--cosmic-primary-light)' }}>Username: root</div>
                  <div style={{ color: 'var(--text-secondary)' }}>Password: admin</div>
                </div>
              </div>
            </div>

            <div style={{ marginBottom: 'var(--spacing-lg)' }}>
              <h3 style={{ fontSize: '1.25rem', marginBottom: 'var(--spacing-sm)' }}>📦 VirtualBox Setup</h3>
              <ul style={{ textAlign: 'left', maxWidth: '500px', margin: '0 auto', color: 'var(--text-secondary)', lineHeight: '1.8' }}>
                <li>Network: Intel PRO/1000 MT Desktop (82540EM) with NAT</li>
                <li>Graphics: Set controller to VMSVGA</li>
                <li>Storage: Attach cosmic-os.iso as IDE/SATA Optical drive</li>
              </ul>
            </div>

            <div className="hero-buttons" style={{ marginTop: 'var(--spacing-xl)' }}>
              <a href="https://github.com/Abel-Ajish/cosmic-os/releases" target="_blank" rel="noopener noreferrer" className="btn btn-primary">
                <span>⬇️</span>
                Download the latest release
              </a>
              <a href="https://github.com/Abel-Ajish/cosmic-os" target="_blank" rel="noopener noreferrer" className="btn btn-secondary">
                <span>⭐</span>
                Star on GitHub
              </a>
            </div>
          </div>
        </div>
      </section>

      {/* Architecture Section */}
      <section className="section">
        <div className="container">
          <div className="text-center">
            <h2>System Architecture</h2>
            <p style={{ maxWidth: '700px', margin: '0 auto var(--spacing-xl)', fontSize: '1.125rem' }}>
              Understanding how cosmic-os layers work together
            </p>
          </div>
          <div className="glass-card" style={{ maxWidth: '900px', margin: '0 auto', padding: 'var(--spacing-xl)' }}>
            <div style={{
              fontFamily: 'monospace',
              fontSize: '1rem',
              lineHeight: '2',
              color: 'var(--cosmic-primary-light)',
              textAlign: 'center',
              overflowX: 'auto'
            }}>
              <div>Hardware</div>
              <div style={{ color: 'var(--text-secondary)' }}>↓</div>
              <div>BIOS/UEFI</div>
              <div style={{ color: 'var(--text-secondary)' }}>↓</div>
              <div>GRUB Bootloader</div>
              <div style={{ color: 'var(--text-secondary)' }}>↓</div>
              <div>Linux Kernel</div>
              <div style={{ color: 'var(--text-secondary)' }}>↓</div>
              <div>Custom Init (PID 1)</div>
              <div style={{ color: 'var(--text-secondary)' }}>↓</div>
              <div>BusyBox Userland</div>
              <div style={{ color: 'var(--text-secondary)' }}>↓</div>
              <div>Custom Applications</div>
            </div>
          </div>
        </div>
      </section>

      {/* Footer */}
      <footer className="footer">
        <div className="container">
          <div className="footer-content">
            <div style={{ color: 'var(--text-secondary)' }}>
              © 2026 cosmic-os. Created by <span style={{ color: 'var(--cosmic-primary-light)', fontWeight: '600' }}>Abel A</span>
            </div>
            <ul className="footer-links">
              <li><a href="https://github.com/Abel-Ajish/cosmic-os" target="_blank" rel="noopener noreferrer" className="footer-link">GitHub</a></li>
              <li><a href="https://github.com/Abel-Ajish/cosmic-os/blob/main/README.md" target="_blank" rel="noopener noreferrer" className="footer-link">Documentation</a></li>
              <li><a href="https://github.com/Abel-Ajish/cosmic-os/blob/main/LICENSE" target="_blank" rel="noopener noreferrer" className="footer-link">MIT License</a></li>
            </ul>
          </div>
        </div>
      </footer>
    </div>
  );
}

export default App;
